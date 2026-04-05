import os
import html
import re
from pathlib import Path


def define_env(env):
    """
    This is the hook for defining variables, macros and filters

    - variables: the dictionary that contains the environment variables
    - macro: a decorator function, to declare a macro.
    """

    include_docs_path = os.path.join(env.project_dir, "docs")

    @env.macro
    def include_file(path, start_line=0, end_line=None):
        normalized_path = path[1:] if path.startswith("/") else path
        full_path = Path(os.path.join(include_docs_path, normalized_path))

        with open(full_path, "r", encoding="utf-8") as f:
            lines = f.readlines()
        line_range = lines[start_line:end_line]
        return "".join(line_range)

    @env.macro
    def code(*args):
        def parse_links(code):
            link_pattern = r"\[(.*?)\]\((.*?)\)"

            return re.sub(link_pattern, r'<a href="\2">\1</a>', html.escape(code))

        def parse(code):
            return parse_links(code)

        result_code = "".join(parse(code) for code in args)

        return f"<code>{result_code}</code>"

    @env.macro
    def linkof(entity_fullname):
        ns_splitted_entity_fullname = entity_fullname.split("::")

        entity_fullname_without_yu = None
        if entity_fullname.startswith("yu::"):
            entity_fullname_without_yu = "/".join(ns_splitted_entity_fullname[1:])
        else:
            entity_fullname_without_yu = entity_fullname

        entity_name = ns_splitted_entity_fullname[-1]

        entity_path = Path(
            os.path.join(
                "/yu/reference/",
                entity_fullname_without_yu.replace("::", "/"),
                "index.html",
            )
        )

        return f"[`{entity_fullname}`]({entity_path})"

    @env.filter
    def link(entity_fullname):
        return linkof(entity_fullname)
