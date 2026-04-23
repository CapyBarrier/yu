const specialIdentifiers = ["unspecified", "see_below"];

function italicizeSpecialIdentifiers(root = document) {
    root.querySelectorAll(".highlight code").forEach((code) => {
        if (code.dataset.specialIdentifiersDone) return;

        const escaped = specialIdentifiers.map((s) =>
            s.replace(/[.*+?^${}()|[\]\\]/g, "\\$&"),
        );

        const regex = new RegExp(`(${escaped.join("|")})`, "g");

        const walker = document.createTreeWalker(
            code,
            NodeFilter.SHOW_TEXT,
            null,
        );

        const targets = [];

        while (walker.nextNode()) {
            const node = walker.currentNode;
            if (regex.test(node.nodeValue)) {
                targets.push(node);
            }
        }

        targets.forEach((node) => {
            const fragment = document.createDocumentFragment();
            const parts = node.nodeValue.split(regex);

            parts.forEach((part) => {
                if (specialIdentifiers.includes(part)) {
                    const span = document.createElement("span");
                    span.style.fontStyle = "italic";
                    span.textContent = part;
                    fragment.appendChild(span);
                } else {
                    fragment.appendChild(document.createTextNode(part));
                }
            });

            node.parentNode.replaceChild(fragment, node);
        });

        code.dataset.specialIdentifiersDone = "true";
    });
}

document.addEventListener("DOMContentLoaded", () =>
    italicizeSpecialIdentifiers(),
);

document.addEventListener("md-content-loaded", () =>
    italicizeSpecialIdentifiers(),
);
