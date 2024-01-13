# Jogo-da-Minhoca-em-C
Prática e revisão de muitos conceitos em C em um só programa. Implementação bem divertida.<br>
Criação do famoso Snake em 2D em C.<br>
Criação com representação do jogo em janela 2D no terminal com captação de tecla<br>

Utilize as setas do teclado para controlar a minhoca.

No início ia largar a ideia, mas acabou ficando bem interessante implementar funções nesse joguinho.
O motivo é que uma função muito importante "flushinp()" deu a entender que não é compatível
com o Windows (meu SO), sendo assim, é necessário teclar cada movimento (sem ENTER). <br><br>
A ideia principal era o jogo continuar rodando e a
cada tecla pressionada, a minhoca em movimento trocava a direção (que é como o jogo funciona), na realidade deu pra implementar, mas o jogo é facilmente burlado aumentando 
a velocidade da minhoca se apertar a tecla mais rápido do que a velocidade de execução definida na main (usleep), já que não é possível limpar o buffer de entrada no ncurses
sem essa função, então preferi deixar na base do I/O mesmo, já que existem métodos para captar a tecla sem necessidade de ENTER, o que faz com que o jogo não fique tão chato, sendo assim, mantive a ideia.<br>

Melhorias serão implementadas periodicamente.
