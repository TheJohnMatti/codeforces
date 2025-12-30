#!/usr/bin/env bash

name="${1:-main}"

if [[ "$name" != *.cpp ]]; then
    name="$name.cpp"
fi

if [[ -e "$name" ]]; then
    echo "File already exists: $name"
    exit 1
fi

cat > "$name" << 'EOF'
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    

    return 0;
}
EOF

echo "Created $name"
