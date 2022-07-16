
- #### Macros
    Each macro identifier is mapped to a value by the parser.
    The regex for the value:
    ```
    [A-Za-z0-9_]+
    ```
    The regex for defining a macro identifier is:
    ```
    @[A-Za-z_][A-Za-z_0-9]*@
    ```
    Example of defining Macro:
    ```
    @ON@ 1;
    ```
    The regex for using a macro identifier is:
    ```
    $[A-Za-z_][A-Za-z_0-9]*$
    ```
    Example of using Macro:
    ```
    ghost = $ON$; //"$ON$" is replaced with "1" by the parser.
    ```
- Update readme with changes according to change of rules
