# CHECKLIST

## Pre-commit (quick)
- [ ] Tests pass (`make test`)
- [ ] Lint passes (`make check`)
- [ ] Format correct
- [ ] No console.log/debug in src
- [ ] No TODO in src (file issues instead)
- [ ] Docs updated if behaviour changed
- [ ] Diffstory written (in build output)

## Pre-release (thorough)
- [ ] Headless test advances 300 frames with zero route failures
- [ ] Frame hash matches reference capture
- [ ] PCM overflow count is zero
- [ ] No unknown S-SMP PC values observed
- [ ] SRAM save/load round-trip verified
- [ ] Both Linux and Windows frontends build
- [ ] ROM hash matches `ROM-REQUIREMENTS.txt`
- [ ] `make doctor` reports all dependencies satisfied

## Domain-specific gates
See `docs/QUALITY_GATES.md` for detailed gates.