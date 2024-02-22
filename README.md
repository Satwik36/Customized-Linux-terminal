# Customized-Linux-terminal


This repository contains the source code for a custom Linux terminal developed from scratch using socket programming. The terminal implements all traditional Linux commands along with additional custom commands such as `myexit`, `mycd`, and `mypwd`.

## Features

- **Socket Programming:** The terminal is implemented using socket programming to facilitate communication between the client-side interface and the server-side terminal logic.

- **Traditional Linux Commands:** All standard Linux commands, such as `ls`, `cd`, `pwd`, `mkdir`, `rm`, `cp`, `mv`, `cat`, etc., are supported and function as expected.

- **Custom Commands:** In addition to traditional commands, the terminal supports custom commands:
  - `myexit`: Exits the custom terminal.
  - `mycd`: Changes the current working directory.
  - `mypwd`: Displays the current working directory.

## Getting Started

To use the custom Linux terminal, follow these steps:

1. Clone this repository to your local machine.
2. Navigate to the `src` directory.
3. Compile the source code using a C/C++ compiler.
4. Run the compiled executable on your Linux system.
5. Connect to the terminal using a client-side interface (e.g., another terminal window or a custom client application).

## Usage

Once the terminal is running, you can use it like any other Linux terminal. Additionally, you can use the following custom commands:

- `myexit`: Type `myexit` and press Enter to exit the custom terminal.
- `mycd`: Type `mycd <directory>` to change the current working directory to the specified directory.
- `mypwd`: Type `mypwd` to display the current working directory.

## Contributing

Contributions to this project are welcome. You can contribute by:
- Reporting bugs or issues
- Suggesting new features or enhancements
- Submitting pull requests for code improvements or fixes

## License

This project is licensed under the [MIT License](LICENSE). Feel free to use, modify, and distribute the code for academic, personal, or commercial purposes.
