import os
import html
import json
import re
from pathlib import Path


def define_env(env):

    REPO_ROOT_PATH = os.path.normpath(os.path.join(env.project_dir, "../"))

    MKDOCS_ROOT_PATH = os.path.join(REPO_ROOT_PATH, "docs")
    DOCS_PATH = os.path.join(MKDOCS_ROOT_PATH, "docs")
    INCLUDE_PATH = os.path.join(DOCS_PATH, "assets/includes")
    INDEX_PATH = os.path.join(REPO_ROOT_PATH, ".cache/yukit/index.json")
    INDEX_JSON = json.load(open(INDEX_PATH, "r"))

    @env.macro
    def name(entity_id):
        return INDEX_JSON[entity_id]["name"]

    @env.macro
    def url(entity_id):
        return Path(INDEX_JSON[entity_id]["url"])

    @env.macro
    def fullname(entity_id):
        return INDEX_JSON[entity_id]["namespace"]

    @env.macro
    def category(entity_id):
        return INDEX_JSON[entity_id]["category"]

    @env.macro
    def status(entity_id):
        return INDEX_JSON[entity_id]["status"]

    @env.macro
    def status_name(entity_id):
        status_map = {
            "planned": "計画中",
            "unimplemented": "未実装",
            "unstable": "未確定",
            "stable": "安定済",
        }

        return status_map[status(entity_id)]

    @env.macro
    def status_mark(entity_id):
        entity_status = status(entity_id)

        status_path = os.path.join(INCLUDE_PATH, f"{entity_status}.md")

        with open(status_path, "r", encoding="utf-8") as f:
            lines = f.readlines()
        return "".join(lines)

    @env.macro
    def ref(entity_id, custom_name=""):

        entity_name = custom_name if custom_name else name(entity_id)
        entity_url = url(entity_id)

        return f"[`{entity_name}`](\\{entity_url})"

    @env.macro
    def ref_fullname(entity_id):

        entity_name = fullname(entity_id)
        entity_url = url(entity_id)

        return f"[`{entity_name}`](\\{entity_url})"

    @env.macro
    def entity_row_begin():
        return "| 名前 | 説明 | バージョン | 状態 |\n| - | - | - | - |"

    @env.macro
    def entity_row(entity_id, description, version="-"):
        entity_ref = ref(entity_id)
        entity_status = status_name(entity_id)

        return f"|{entity_ref} | {description} | {version} | {entity_status}|"

    @env.macro
    def include_file(path, start_line=0, end_line=None):
        full_path = Path(os.path.join(DOCS_PATH, path))

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
