mkdir -p ./dist/$(dirname ${1%".c"})

mpicc -w ./scripts/$1 -fopenmp -lm -o ./dist/${1%".c"}
mpirun -np $2 ./dist/${1%".c"}