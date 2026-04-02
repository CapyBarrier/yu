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


    @env.macro
    def include_file(filename, start_line=0, end_line=None):
        """
        Include a file, optionally indicating start_line and end_line
        (start counting from 0)
        The path is relative to the top directory of the documentation
        project.
        """
        full_filename = Path(os.path.join(env.project_dir, filename))
        with open(full_filename, 'r', encoding="utf-8") as f:
            lines = f.readlines()
        line_range = lines[start_line:end_line]
        return ''.join(line_range)

    @env.macro
    def code_in_link(code):
        escaped_code = html.escape(code)
        pattern = r'\[(.*?)\]\((.*?)\)'
        html_code = re.sub(pattern, r'<a href="\2">\1</a>', escaped_code)

        return "<code>" + html_code + "</code>"

    @env.macro
    def entity_link(entity, relative=""):
        if relative == "":
            return f"[`{entity}`]({entity}/)"
        else:
            return f"[`{entity}`]({relative}/{entity}/)"