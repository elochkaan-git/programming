#!/usr/bin/env bash
set -euo pipefail

VERSION_FILE="VERSION"

# Если файла нет — создаём с первой версией
if [[ ! -f $VERSION_FILE ]]; then
  echo "0.1.0" > $VERSION_FILE
fi

# Читаем текущую версию
CURRENT_VERSION=$(cat $VERSION_FILE)
IFS='.' read -r MAJOR MINOR PATCH <<< "$CURRENT_VERSION"

# Смотрим коммиты с последнего тега или версии
COMMITS=$(git log --pretty=format:"%s" $(git rev-list -n 1 HEAD -- "$VERSION_FILE")..HEAD)

BUMP="patch"

while read -r COMMIT; do
  if [[ $COMMIT == *"BREAKING CHANGE"* ]] || [[ $COMMIT == *"!:"* ]]; then
    BUMP="major"
    break
  elif [[ $COMMIT == feat:* ]]; then
    BUMP="minor"
  fi
done <<< "$COMMITS"

case $BUMP in
  major)
    ((MAJOR+=1))
    MINOR=0
    PATCH=0
    ;;
  minor)
    ((MINOR+=1))
    PATCH=0
    ;;
  patch)
    ((PATCH+=1))
    ;;
esac

NEW_VERSION="$MAJOR.$MINOR.$PATCH"
echo "v$NEW_VERSION" > $VERSION_FILE
git tag "v$NEW_VERSION" HEAD

echo "Version bumped: v$CURRENT_VERSION → v$NEW_VERSION"
