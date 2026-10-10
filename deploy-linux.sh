#!/bin/bash
# deploy-linux.sh — stage dist/linux/ with binary and run.sh launcher
set -e

BUILD_DIR="${BUILD_DIR:-build}"
HOST="${1:-}"

# Build Release if not already built
if [ ! -f "${BUILD_DIR}/frontend/linux/utopia-linux" ]; then
    echo "Building Release..."
    cmake -S . -B "${BUILD_DIR}" -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=ON
    cmake --build "${BUILD_DIR}" -j"$(nproc)"
fi

# Stage dist/linux/
rm -rf dist/linux
mkdir -p dist/linux
cp "${BUILD_DIR}/frontend/linux/utopia-linux" dist/linux/
cp "${BUILD_DIR}/frontend/linux/headless-test" dist/linux/ 2>/dev/null || true

cat > dist/linux/run.sh << 'RUNEOF'
#!/bin/sh
DIR="$(cd "$(dirname "$0")" && pwd)"
exec "${DIR}/utopia-linux" "$@"
RUNEOF
chmod +x dist/linux/run.sh

if [ -n "$HOST" ]; then
    echo "Uploading to ${HOST}:~/utopia-build/"
    scp -r dist/linux/ "${HOST}:~/utopia-build/"
fi

echo "Deployed to dist/linux/"