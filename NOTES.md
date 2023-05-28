1. Generate *.asm* file with `cl /c /FA /GS- message_box.cpp`
2. Add `assume fs:nothing` to the top of the generated *.asm* file.
3. Getting rid of imports. Comment out the following lines:
  - `INCLUDELIB LIBCMT` 
  - `INCLUDELIB OLDNAMES`
  - `include listing.inc`
4. Generate *object file* with: `ml /c message_box.asm`
5. Compile with: `link message_box.obj /entry:main`