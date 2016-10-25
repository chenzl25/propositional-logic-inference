# lexical rule
# ----------------------------------
# usage:
# [%] [name] [string]...
# [$] [name] [regular expression]
# ----------------------------------

% reserve_words symbols relations KB alpha
% operators ! <=> => := ( ) ; | & : ,
$ identifier [a-zA-Z_][a-zA-Z0-9]*

# default comment is #
