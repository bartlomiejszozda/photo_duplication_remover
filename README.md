# photo_duplication_remover
photo duplication remover

## To develop:
cd docker
./build.sh
./run.sh
connect to docker using toolchain (i.e. clion toolchain)
run tests


TODO:
- windows support
- multiple dirs
- use multithreading

- tests for DuplicatedFile and DuplicationCandidatesFinder
- use std::range in findUniqueFiles if possible
- add more keys (other than Differentiator), use they as templates params and use concepts
