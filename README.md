# tin-core
Services for Tin platform projects.

# Guidelines

- DO NOT work around tin-core behaviour. Fix it.
- tin-core will never have a stable API. There is no deprecation; 
  APIs should be removed immediately after no more projects depend
  on it.
- Code should be just general enough to serve all projects. 
  Ask if you think your code is too generic or too specific.
- Try not to write objects that require duplication or additional
  data in UI space (e.g. friends in toxcore, the client has to
  copy out essential data like name constantly)
