# GEMINI.md — Antigravity-Specific Configuration

> Antigravity overrides only. General rules are in AGENTS.md.

---

## Autonomy

- Use **Planning Mode** for new phases or any task touching multiple files
- Use **Fast Mode** for single-file fixes, typos, or small edits
- Always show a plan and wait for approval before modifying more than 3 files at once

---

## Response Format

After every task, report in this format:

```bash
## Changes
- Added: <files>
- Modified: <files>
- Deleted: <files>

## Test Steps
1. <command to run>
2. <what to expect>

## Reminder
- [ ] Update docs/CHANGELOG.md
- [ ] Tick phase in docs/plans/master-plan.md
```

---

## Artifacts

- Generate an **implementation plan** as an Artifact before coding any phase
- If UI is involved, generate a **terminal mockup** in the Artifact first
- Keep Artifacts short — bullet points, not paragraphs

---

## Workflows

- `/phase <number>` — start a phase: read plan file, generate Artifact, then implement
- `/check` — review current state: compile, list what's done vs pending in master-plan.md
- `/changelog` — append today's completed work to docs/CHANGELOG.md

---

## Constraints

- Never open a browser — this is a C++ terminal project, no web testing needed
- Never install packages — only standard g++ and make
- If unsure about lib/ interface, read the relevant `.hpp` file before assuming
