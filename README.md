# SimannC

Netlib f77 simulated annealing versiyonunun C dilinde yeniden ve geliştirilerek yapılmış implementasyonu

Su an

gcc -c simannFuncs.c objectiveFunc.c simann.c -Wall && gcc main.c *.o -o opt.x -Wall

komutu ile derlenebilir