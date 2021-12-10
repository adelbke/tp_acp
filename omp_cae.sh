mkdir -p ./dist/$(dirname ${1%".c"})

gcc -w ./scripts/$1 -fopenmp -lm -o ./dist/${1%".c"}
./dist/${1%".c"}