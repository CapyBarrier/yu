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
    INDEX_PATH = os.path.join(REPO_ROOT_PATH, "yukit/index.json")
    INDEX_JSON = json.load(open(INDEX_PATH, "r"))

    def entity_exists(entity_name):
        return entity_name in INDEX_JSON

    def normalize_entity_name(entity_name):
        return re.sub(r"[<(].*", "", entity_name)

    @env.macro
    def fullname(entity_name):
        return INDEX_JSON[entity_name]["fullname"]

    @env.macro
    def qualified_name(entity_name):
        return INDEX_JSON[entity_name]["qualified_name"]

    @env.macro
    def identifier(entity_name):
        return INDEX_JSON[entity_name]["identifier"]

    @env.macro
    def namespace(entity_name):
        return INDEX_JSON[entity_name]["namespace"]

    @env.macro
    def alias(entity_name):
        return INDEX_JSON[entity_name]["alias"]

    @env.macro
    def category(entity_name):
        return INDEX_JSON[entity_name]["category" ""]

    @env.macro
    def status(entity_name):
        return INDEX_JSON[entity_name]["status"]

    @env.macro
    def url(entity_name):
        return Path(INDEX_JSON[entity_name]["url"])

    @env.macro
    def status_name(entity_name):
        status_map = {
            "planned": "計画中",
            "unimplemented": "未実装",
            "unstable": "未確定",
            "stable": "安定",
        }
        return status_map[status(entity_name)]

    @env.macro
    def status_mark(entity_name):
        entity_status = status(entity_name)

        status_path = os.path.join(INCLUDE_PATH, f"{entity_status}.md")

        with open(status_path, "r", encoding="utf-8") as f:
            lines = f.readlines()
        return "".join(lines)

    @env.macro
    def ref(entity_name, style=identifier):
        original_name = entity_name
        normalized_name = normalize_entity_name(original_name)

        suffix = original_name[len(normalized_name) :]

        entity_url = url(normalized_name)

        styled_name = style(normalized_name) + suffix

        return f"[`{styled_name}`]({entity_url})"

    @env.macro
    def entity_row_begin():
        return "| 名前 | 説明 | バージョン | 状態 |\n| - | - | - | - |"

    @env.macro
    def entity_row(entity_name, description, version="-"):
        entity_ref = ref(entity_name)
        entity_status = status_name(entity_name)

        return f"|{entity_ref} | {description} | {version} | {entity_status}|"

    @env.macro
    def include_file(path, start_line=0, end_line=None):
        full_path = Path(os.path.join(DOCS_PATH, path))

        with open(full_path, "r", encoding="utf-8") as f:
            lines = f.readlines()
        line_range = lines[start_line:end_line]
        return "".join(line_range)
