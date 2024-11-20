#docker build -t photo_duplication_remover .
set -xeu
DOCKER_BUILDKIT=1 docker build --progress=plain -t photo_duplication_remover .