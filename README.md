# VAT-Calculator
[![GuardRails badge](https://api.guardrails.io/v2/badges/simonpla/VAT-Calculator.svg?token=c034fde815592b98a32c5b8f210db2df53cc95526436c50b4bbc70d42089df79&provider=github)](https://dashboard.guardrails.io/gh/simonpla/82791)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/4c285b087e074128ac78eea3bedbf993)](https://www.codacy.com/gh/simonpla/VAT-Calculator/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=simonpla/VAT-Calculator&amp;utm_campaign=Badge_Grade)

Calculates VAT from and to values, with flexible input methods, like importing hundreds of values from CSV files.

It is powered by wxWidgets, a cross-platform GUI library for C++.
It uses cmake for easy compilation on Windows, macOS and Linux, credits to [JustDevTutorials](https://www.youtube.com/channel/UC4Q-KGKCeFbBpaAqwllCDqQ) and his [wx_cmake_template](https://github.com/lszl84/wx_cmake_template).

Multi-language support is available.

## Compile from source
Currently the only available installation method is compiling from source.
To do this, clone the repository using git:

`git clone https://github.com/simonpla/VAT-Calculator.git`

After that `cd` into the directory and run the following commands:
```
cmake -S. -Bbuild
cmake --build build
```
The executable will be located under `build/subprojects/Build/wx_cmake_template_core/main` in Linux and macOS and under `build/subprojects/Build/wx_cmake_template_core/main/Debug/main.exe` in Windows.
