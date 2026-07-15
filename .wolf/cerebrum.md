# Cerebrum

> OpenWolf's learning memory. Updated automatically as the AI learns from interactions.
> Do not edit manually unless correcting an error.
> Last updated: 2026-07-15

## User Preferences

<!-- How the user likes things done. Code style, tools, patterns, communication. -->

## Key Learnings

- **Project:** AngeES
- **Description:** To get the newest releases of the game, [click here](https://github.com/Engine-Simulator/engine-sim-community-edition).
- **Driveline/clutch "flex" backport (1.14):** modeled as a torsional spring-damper `ForceGenerator` (`include/driveline_flex.h`, `src/driveline_flex.cpp`) that REPLACES the rigid `ClutchConstraint` when `simulate_flex` is on. It integrates a bounded wind-up angle and clamps transmitted torque to the clutch capacity (`maxClutchTorque * pressure`) → stable by construction (can't inject runaway energy) and slips past capacity. Owned by `Transmission`; vehicle + clutch flex combine as series springs in `Transmission::addToSystem`. Engine uses single-stage symplectic `NsvOdeSolver`, so integrating state inside `ForceGenerator::apply()` is correct (one call/step, `state->dt` = full timestep). `[bool]` .mr inputs bind directly to C++ `bool` members (precedent: `flip_display`).
- **Build toolset MUST match the CMake cache:** `build/CMakeCache.txt` pins `CMAKE_CXX_COMPILER` to VS2022 (14.44). Entering the VS18 (`-latest`) dev shell mixes VS18's newer STL headers with the older cached compiler → `error C2338 STL1001: Unexpected compiler version`. Always `Enter-VsDevShell -VsInstallPath "C:\Program Files\Microsoft Visual Studio\2022\Community"`, not `-latest`.
- **Test suite has PRE-EXISTING failures unrelated to gameplay code:** `GasSystemTests.PressureEquilibriumMaxFlow*` (x3), `FunctionTests.FunctionGaussianTest`, and `SynthesizerTests.*` (SEH 0xC0000005, needs audio device). These fail on numerical tolerance / headless audio, not from feature work — don't chase them when verifying unrelated changes.

## Do-Not-Repeat

<!-- Mistakes made and corrected. Each entry prevents the same mistake recurring. -->
<!-- Format: [YYYY-MM-DD] Description of what went wrong and what to do instead. -->

## Decision Log

<!-- Significant technical decisions with rationale. Why X was chosen over Y. -->
