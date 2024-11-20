#!/bin/bash
set -xeu

docker run -d \
  --network=host \
  --name=photo_duplication_remover_container \
  --entrypoint=/usr/sbin/sshd \
  photo_duplication_remover -D