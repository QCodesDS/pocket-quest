---
description:
---

# Workflow: /changelog

Trigger: `/changelog`
Purpose: Append today's completed work to docs/CHANGELOG.md

## Steps

1. **Ask** what was completed in this session
   (if not already clear from context)

2. **Format** the entry:

   ```
   ## [YYYY-MM-DD] — Phase XX: <Phase Name>

   ### Completed
   - Added: <file list>
   - Modified: <file list>
   - Feature: <what works now>

   ### Notes
   - <any known issues or decisions made>
   ```

3. **Append** to `docs/CHANGELOG.md` — never overwrite existing entries

4. **Tick** completed items in `docs/plans/master-plan.md`
   - Change `⬜` to `✅` for finished phases

5. Confirm: "CHANGELOG updated. master-plan.md ticked."
