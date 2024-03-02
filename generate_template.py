import pathlib
from typing_extensions import Annotated

import typer
from rich import print

app = typer.Typer()

PROGRAM_TEMPLATE: str = """/*
ID: bwang101
TASK: {task}
LANG: C++14
*/

#include <cstddef>	  // std::size_t
#include <fstream>	  // std::ifstream, std::ofstream
#include <iostream>	  // std::endl
#include <string>	  // std::string

auto main() -> int {{
    const std::string file_base_name = "{task}";
    std::ifstream fin(file_base_name + ".in");
    std::ofstream fout(file_base_name + ".out");

    std::size_t N = 0;
    fin >> N;

    fout << 0 << std::endl;
    return 0;
}}
"""


@app.command("gen")
def create_solution_template(
        chapter: Annotated[int, typer.Argument(help="Chapter number of problem")],
        section: Annotated[int, typer.Argument(help="Section number of problem")],
        title: Annotated[str, typer.Argument(help="Full problem name")],
        program_name: Annotated[str, typer.Argument(help="Task name")],
        dry_run: Annotated[bool, typer.Option(help="Adding this option will not result in writing any files")] = False
    ) -> None:
    """
    Create a <program_name>.cpp and <program_name>.in under directory
    chapter<chapter>/section<section>/<title>/, as well as add an entry to the
    section README.md
    """
    file_base: str = f"chapter{chapter}/section{section}/{title.lower().replace(' ', '_')}/{program_name}"
    cpp_file: pathlib.Path = pathlib.Path(file_base + ".cpp")
    in_file: pathlib.Path = pathlib.Path(file_base + ".in")

    if cpp_file.exists():
        print(f"[bold yellow]File {cpp_file} already exists; aborting")
        raise typer.Exit()

    print("[bold white]Generating directories...")
    if not dry_run:
        cpp_file.parent.mkdir(exist_ok=True, parents=True)

    print(f"[bold white]Generating {str(cpp_file)}...")
    if not dry_run:
        with cpp_file.open("w") as f:
            f.write(PROGRAM_TEMPLATE.format(task=program_name))

    print(f"[bold white]Generating {str(in_file)}...")
    if not dry_run:
        with in_file.open("w") as f:
            f.write("")

    readme_file: pathlib.Path = pathlib.Path(f"chapter{chapter}/section{section}/README.md")
    print(f"[bold white]Adding entry to {readme_file}")
    if not dry_run:
        with readme_file.open("a") as f:
            f.write(f"* {title}: previously submitted on ????-??-??. Last submitted on ????-??-??. This was submission #?.\n")

    print("[bold cyan]Finished!")


if __name__ == "__main__":
    app()
