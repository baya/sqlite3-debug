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

### cheat sheet

- `M-.’ (‘find-tag’) – find a tag, that is, use the Tags file to look up a definition. If there are multiple tags in the project with the same name, use `C-u M-.’ to go to the next match.
- ‘M-x find-tag-other-window’ – selects the buffer containing the tag’s definition in another window, and move point there.
- ‘M-*’ (‘pop-tag-mark’) – jump back
- ‘M-x tags-search’ – regexp-search through the source files indexed by a tags file (a bit like ‘grep’)
- ‘M-x tags-query-replace’ – query-replace through the source files indexed by a tags file
- `M-,’ (‘tags-loop-continue’) – resume  ‘tags-search’ or ‘tags-query-replace’ starting at point in a source file
- ‘M-x tags-apropos’ – list all tags in a tags file that match a regexp
- ‘M-x list-tags’ – list all tags defined in a source file
