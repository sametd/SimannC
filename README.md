# SimannC

Netlib f77 simulated annealing versiyonunun C dilinde yeniden ve geliştirilerek yapılmış implementasyonu

Su an

gcc -c simannFuncs.c objectiveFunc.c simann.c -lm -Wall && gcc main.c *.o -o opt.x -lm -Wall

komutu ile derlenebilir. Buraya ekstra test fonksiyonları ve bir Makefile gelebilir, gelmeyebilir de :)

Samet.
