<div align="center">

# Starlight &mdash; Runtime Engine

[![Issues](https://img.shields.io/github/issues/NekkoDroid/Starlight)](https://github.com/NekkoDroid/Starlight/issues)
[![Pull Requests](https://img.shields.io/github/issues-pr/NekkoDroid/Starlight)](https://github.com/NekkoDroid/Starlight/pulls)
[![Discussions](https://img.shields.io/github/discussions/NekkoDroid/Starlight)](https://github.com/NekkoDroid/Starlight/discussions)
[![License](https://img.shields.io/github/license/NekkoDroid/Starlight)](#copyright-license)

*Welcome to **Starlight**, a cross-platform 3D game engine I am making as a learning project.*
*The goal of this project is to end up as a simple, usable, general purpose game engine for desktop platforms.*
</div>

## :toolbox: Development

## Prerequisites

- [Git](https://git-scm.com/download) for version control
- [Node.js](https://nodejs.org/en/download) for certain scripts
- [CMake](https://cmake.org/download) for the C++ build system generator
- A C++20 compatible compiler ([Clang](https://clang.llvm.org), [MSVC](https://visualstudio.microsoft.com), [GCC](https://gcc.gnu.org))
- (Recommended) [Ninja](https://ninja-build.org) as the default build system
- (Recommended) [vcpkg](https://github.com/microsoft/vcpkg) for C++ package management
- (Recommended) An IDE with code completion and syntax highlighting, such as:
	- [Visual Studio Code](https://code.visualstudio.com)
	- [Visual Studio 2022](https://visualstudio.microsoft.com/vs)
	- [JetBrains Rider](https://www.jetbrains.com/rider)

### :rocket: Getting started

Set up the repository by running the following commands:

```sh
$ git clone https://github.com/NekkoDroid/Starlight
$ cd ./Starlight
# Enable the provided git hooks
$ git config core.hooksPath .githooks
```

To update the source code just run the following command:

```sh
$ git pull
```

### :hammer_and_wrench: Building the project

Generate the build system by running the following command:

```sh
$ cmake --preset default
# or to use vcpkg (requires $VCPKG_ROOT set)
$ cmake --preset vcpkg
```

Now build the project by running the following command:

```sh
# This will output the build results in ./Install
$ cmake --build ./Build --config [Debug|RelWithDebInfo|Release] --target install
```

## :handshake: Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any
contributions you make are **greatly appreciated**:

- [Start a discussion](https://github.com/NekkoDroid/Starlight/discussions) for any suggestions you have
- [Submit a new issue](https://github.com/NekkoDroid/Starlight/issues) if you find any new problems with the project
- [Open a pull request](https://github.com/NekkoDroid/Starlight/pulls) to submit fixes, enhancements or similar

> When committing make sure your commit messages follow the [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0) format.

## :copyright: License

<table>
<tr>
<td width="160px">

![Apache Software Foundation](https://www.apache.org/foundation/press/kit/asf_logo.svg)
</td>
<td>

This project is distributed under the [Apache 2.0](https://www.apache.org/licenses/LICENSE-2.0) license. For further
information read the included [LICENSE](LICENSE.txt) files. [TL;DR](https://www.tldrlegal.com/l/apache2) you can do
whatever you want, as long as you include the required notices.
</td>
</tr>
</table>

<details>
<summary><b>Permissions</b></summary>
<blockquote>

<details>
<summary><em>Commercial Use</em></summary>
<blockquote>
The licensed material and derivatives may be used for commercial purposes.
</blockquote>
</details>

<details>
<summary><em>Modification</em></summary>
<blockquote>
The licensed material may be modified.
</blockquote>
</details>

<details>
<summary><em>Distribution</em></summary>
<blockquote>
The licensed material may be distributed.
</blockquote>
</details>

<details>
<summary><em>Patent use</em></summary>
<blockquote>
This license provides an express grant of patent rights from contributors.
</blockquote>
</details>

<details>
<summary><em>Private use</em></summary>
<blockquote>
The licensed material may be used and modified in private.
</blockquote>
</details>

</blockquote>
</details>

<details>
<summary><b>Limitations</b></summary>
<blockquote>

<details>
<summary><em>Trademark use</em></summary>
<blockquote>
This license explicitly states that it does NOT grant trademark rights, even though licenses without such a statement
probably do not grant any implicit trademark rights.
</blockquote>
</details>

<details>
<summary><em>Liability</em></summary>
<blockquote>
This license includes a limitation of liability.
</blockquote>
</details>

<details>
<summary><em>Warranty</em></summary>
<blockquote>
This license explicitly states that it does NOT provide any warranty.
</blockquote>
</details>

</blockquote>
</details>

<details>
<summary><b>Conditions</b></summary>
<blockquote>

<details>
<summary><em>License and copyright notice</em></summary>
<blockquote>
A copy of the license and copyright notice must be included with the licensed material.
</blockquote>
</details>

<details>
<summary><em>State changes</em></summary>
<blockquote>
Changes made to the licensed material must be documented.
</blockquote>
</details>

</blockquote>
</details>
