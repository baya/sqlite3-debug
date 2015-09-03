## c tags

```bash
(find . -name '*.[ch]'
 find . -name '*.ad[bs]'
)|grep -v "CVS/Base" | sort | xargs etags -a
```

示例:

```
M-. sqlite3_step
```
