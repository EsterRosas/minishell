# 42minishell
This project is about developing a simplified version of the bash shell.

## Sections
Minishell project is divided into 4 distinct parts:
- **Lexer**: Takes the entered line as input and reads through the line word by word using white space as delimiters.
- **Parser**: Groups the different nodes together based on the tokens (i.e. `|`, `<`, `>>`, `>>`, `>`). Each group becomes a command.
- **Expander**: Takes variables, identified by `$`, and replaces them with their value from the environment variables.
- **Executor**: Is the one in charge of executing the final command.

## Sources
- [readline docs](https://web.mit.edu/gnu/doc/html/rlman_2.html)
- [Getting Started 1](https://harm-smits.github.io/42docs/projects/minishell)
- [Getting Started 2](https://github.com/madebypixel02/minishell)
- [Pipex YouTube](https://www.youtube.com/playlist?list=PLK4FY1IoDcHG-jUt93Cl7n7XLQDZ0q7Tv)
- [Bash Parser](https://mywiki.wooledge.org/BashParser)
- [Bash Commands and Arguments](https://mywiki.wooledge.org/BashGuide/CommandsAndArguments)
