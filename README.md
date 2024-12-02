# photo_duplication_remover
photo duplication remover

## To develop:
cd docker
./build.sh
./run.sh
connect to docker using toolchain (i.e. clion toolchain)
run tests


TODO:
- filter may filter anything, not path only (but now I cant imagine the usage of it)
- optimised duplications finder by injecting comparators to std::unordered_map
- filter duplications using multithreading
- tests for DuplicatedFile and DuplicationCandidatesFinder
- use std::range in findUniqueFiles if possible
- add more keys (other than Differentiator, use they as templates params and use concepts
- multiple dirs
- photos only
- filter duplications by name
- make sure about finding all (multiple) duplications
- make sure all duplications have the same size, date of file creation, date of photo taken
- make sure all duplications contains same data
- allow removal (by loging or moving to another directory)
- calculate hash values of photos
- filter duplications based hash calculations


- windows support
- movies duplication removal
- files duplication removal