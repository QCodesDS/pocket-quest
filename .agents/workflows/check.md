---
description:
---

# Workflow: /check

Trigger: `/check`
Purpose: Review current project state

## Steps

1. **Read** `docs/plans/master-plan.md`
   - List completed phases ✅
   - List pending phases ⬜
   - Identify current phase

2. **Read** `docs/CHANGELOG.md`
   - Summarize what has been done so far

3. **Scan** `app/` directory
   - List files that exist
   - Flag any files in master-plan that are missing

4. **Compile check**
   - Run `make` and report result
   - List any warnings or errors

5. **Report**

   ```
   ## Project Status
   - Current phase: XX
   - Completed: X/8 phases
   - Last changelog entry: <date>

   ## Compile
   - Result: OK / ERRORS
   - Warnings: <list>

   ## Next step
   - <what to do next>
   ```
