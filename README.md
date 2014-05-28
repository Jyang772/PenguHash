PenguSniff
==========

A simple file integrity monitor


========

To create an online installer:

`cd Release`

`./repogen -p packages -c config/config.xml repository`

To create an online only binary:

`./binarycreator -p packages -c config/config.xml -n installer`


* -e == exclude packages that will be downloaded

* -i == include packages in online repository

* -n == online only binary

=========


Installation:

Requires Sudo if user chooses to download/install dependencies
