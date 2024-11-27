# photo_duplication_remover
photo duplication remover

## To develop:
cd docker
./build.sh
./run.sh
connect to docker using toolchain (i.e. clion toolchain)
run tests


TODO:
- tests for DuplicatedFile and DuplicatedFiles
- use std::range in findUniqueFiles if possible
- add more keys (other than FileNameSize, use they as templates params and use concepts
- multiple dirs
- photos only
- find duplications by name
- make sure about finding all (multiple) duplications
- make sure all duplications have the same size, date of file creation, date of photo taken
- make sure all duplications contains same data
- allow removal (by loging or moving to another directory)
- calculate hash values of photos
- find duplications based hash calculations


- windows support
- movies duplication removal
- files duplication removal