# MinMail

A simple utility based on https://github.com/jstedfast/gmime to
extract attachments from RFC822 files, AKA "Maildir files", and to
optionally **replace** the main part of such files with only the
**plain text body**.  See `--wreak-havok`.

## Requirements

https://github.com/jstedfast/gmime 3.2.8 or newer.

If you are using Linux and your version of gmime is too old, you can
do the following to use a locally built libgmime.

```
git clone https://github.com/jstedfast/gmime
cd gmime
./autoconf.sh
make
```

```
cd ..
git clone https://github.com/plujon/minmail
cd minmail
make GMIME_SRC=../gmime
```

One way to get a local Maildir is to use
[offlineimap](https://www.offlineimap.org/).

## Why

Before:

```
$ du -sh Read
869M
```

After:

```
$ du -sh Read
31M
$ ls pieces/*.pdf | wc -l
24
```

## Examples

To copy the parts of a single message into pieces/ :

    minmail message.eml

To do surgery on message.eml, ripping out its guts and leaving only the text/plain part:

    minmail --wreak-havok message.eml

## WARNING

Using `--wreak-havok` might very well **DESTROY YOUR EMAIL**.

So, don't use it unless you make backups and can verify it doesn't
destroy mail you care about.
