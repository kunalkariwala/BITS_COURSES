# Comments tests

IP

```
//not keywords: pause, hard_drop; not strings: "ab_21"; board(30,40);
//not arrays: [12,13]; [{"L",#123456}]
```

OP

```
<COMMENT><COMMENT>
```

# Testing strings

IP

```
"not scanned as keywords: on off board pireces"
```

OP

```
<STRING,"not scanned as keywords: on off board pireces">
```

The Following are invalid tokens

```
"invalid_token 
```

# Testing assignments

IP

```
rotate = "K_UP"; 

rotate = 0; //should tokenize, but later phase may report errors

scoring = [0, 40];

pieces = [{"L",#FFFFFF}, {"I",#111111}];
```

OP

```
<ROTATE><RELOP,EQ><STRING,"K_UP"><EOS>

<ROTATE><RELOP,EQ><NUMBER,0><EOS><COMMENT>

<SCORING><RELOP,EQ><OPEN_SQUARE><NUMBER,0><COMMA><NUMBER,0><COMMA><CLOSE_SQUARE><EOS>

<PCS><RELOP,EQ> <OPEN_SQUARE> <OPEN_CURLY><STRING,"L"><COMMA><COLOR,#FFFFFF><NUMBER,0><CLOSE_CURLY><COMMA> <OPEN_CURLY><STRING,"I"><COMMA><COLOR,#111111><CLOSE_CURLY>  <CLOSE_SQUARE> <EOS>
```

# Misc Tests

IP

```
[{"L",#ffffff}];
ghost = on;
```

OP

```
<OPEN_SQUARE> <OPEN_CURLY><STRING,"L"><COMMA><COLOR,#FFFFFF><NUMBER,0><CLOSE_CURLY> <CLOSE_SQUARE> <EOS>

<GHOST><RELOP,EQ><BOOL,1><EOS>
```