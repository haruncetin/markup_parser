# Attribute Parser of Hackerrank

This code is created from Attribute Parser challenge of Hackerrank platform. It takes a list of html-like xml markup expressions and parses all. Then it can be accessed by "." for tags and "~~" for attributes of tags (i.e. tag1~value tag1.tag2~name).

Example input:
4 3
<tag1 value = "HelloWorld">
<tag2 name = "Name1">
</tag2>
</tag1>
tag1.tag2~name
tag1~name
tag1~value

Example output:
Name1
Not Found!
HelloWorld
