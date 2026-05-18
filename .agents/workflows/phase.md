---
description:
---

# Workflow: /phase

Trigger: `/phase <number>`
Example: `/phase 02`

## Steps

1. **Read** `docs/plans/phase-<number>-*.md`
   - Identify checklist items
   - Note expected output and test steps

2. **Plan** — generate an Artifact with:
   - Files to create / modify
   - Key logic decisions
   - Potential issues
   - Wait for approval before proceeding

3. **Implement** — follow checklist top to bottom
   - Create files in correct directories
   - Apply rules from `.agents/rules/`
   - Apply skills from `.agents/skills/` as needed

4. **Verify** — after implementation:
   - Check compile: `make` (no errors, no warnings)
   - List all files changed

5. **Report** using format from GEMINI.md

6. **Remind** to:
   - Update `docs/CHANGELOG.md`
   - Tick completed items in `docs/plans/master-plan.md`
