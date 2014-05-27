PenguSniff
==========

A simple file integrity monitor


========

To create an online installer:

`./repogen -p packages -c config/config.xml repository`

To create a binary:

`./binarycreator -p packages -c config/config.xml -e installer`


-e == exclude packages that will be downloaded

-i == include packages in online repository
