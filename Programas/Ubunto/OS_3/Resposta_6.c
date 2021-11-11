/*
O Jantar dos filósofos foi proposto por Dijkstra em 1965 como um problema de sincronização. 
A partir de então todos os algoritmos propostos como soluções de sincronização acabaram sendo relacionados ou testados contra o problema do Jantar dos filósofos.

** DEFINIÇÃO DO PROBLEMA DO JANTAR DOS FILÓSOFOS **

Cinco filósofos estão sentados em uma mesa redonda para jantar. Cada filósofo tem um prato com espaguete à sua frente. 
Cada prato possui um garfo para pegar o espaguete. O espaguete está muito escorregadio e, para que um filósofo consiga comer, será necessário utilizar dois garfos. 

Cada filósofo alterna entre duas tarefas: comer ou pensar. Quando um filósofo fica com fome, ele tenta pegar os garfos à sua esquerda e à sua direita; um de cada vez, independente da ordem. 
Caso ele consiga pegar dois garfos, ele come durante um determinado tempo e depois recoloca os garfos na mesa. Em seguida ele volta a pensar.

Por definição, o problema em questão é:

Você é capaz de propor um algoritmo que implemente cada filósofo de modo que ele execute as tarefas de comer e pensar sem nunca ficar travado?

 ** Qual o problema? **

O problema é coordenar o uso dos garfos de maneira que nenhum filósofo fique com fome. Esse problema exemplifica muito bem muitas soluções e muitos problemas encontrados no sincronismo. 
Pode facilmente ocorrer o deadlock (uma situação em que ocorre um impasse, e dois ou mais processos ficam impedidos de continuar suas execuções, esperando uns pelos outros.) 
se cada filósofo pegar o seu garfo da esquerda e se recusar a liberá-lo até ter comido. Pode ocorrer a inanição (starvation) e um filosofo nunca mais comer.

*/
// Um programa que define um filósofo:

void take_fork()
{
  if (n_forks >= 0 || n_forks < 2)
  {

    while (!table.get_one_fork(philosopher_id))
    {

            printf("Philosopher %d  waiting a fork..\n", philosopher_id;
            sleep_for(milliseconds(rand() % 5000));
    }

    n_forks++;
  }
}

void exist()
{

  while (1)
  {

    think();
    take_fork();
    take_fork();
    eat();
    put_fork();
    put_fork();
  }
}
/*

O grande problema nesse algoritmo é que existem momentos em que se todos os filósofos pegarem um garfo, todos irão ficar parados para sempre aguardando o segundo 
garfo ficar disponível; gerando assim um Deadlock.


Nesse caso podemos citar a região crítica: área de código de um algoritmo que acessa um recurso compartilhado que não pode ser acedido concorrentemente por mais de uma linha de execução,
ela é importante para a implementação de exclusão mútua, usada para evitar condições de corrida.

Uma condição de corrida é uma falha num sistema ou processo em que o resultado do processo é inesperadamente dependente da sequência ou sincronia doutros eventos.
Assim, depende muito qual filosofo vai pegar qual garfo e em que dado (rand() % 5000) tempo, podendo ocasionar uma condição de corrida entre eles.

*/
//** IMPORTANCIA DO SEMÁFORO **

/*
O uso do semáforo irá garantir que haja exclusão mútua (mutex), onde apenas um filósofo estará com um determinado garfo por vez. Não haverá starvation nem deadlock.

No problema do Jantar dos filósofos a seção crítica da execução de um filósofo é a operação de comer, que necessariamente, precisa utilizar os dois garfos. 
Nessa nova implementação iremos representar cada garfo como um mutex. Eles serão controlados pelas instruções que irão trabalhar na forma do nosso semáforo. 
Logo após o filósofo terminar de comer os dois garfos que estavam com ele serão liberados. O sistema operacional garantirá que outras threads interessadas no recurso liberado 
sejam escalonadas para executar e tentar pegar os garfos livres.

Assim saindo de um sistema de deadlock para um livelock.

A principal diferença entre livelock e deadlock é que os threads não serão bloqueados, em vez disso eles tentarão responder uns aos outros continuamente. 
Os dois círculos (threads ou processos) tentarão dar espaço ao outro.

Irei deixar um programa jantar_dos_filosofos.c no arquivo .rar para observarmos o sistema de semáforo e como saimos do deadlock e starvation.

*/

// ** PROBLEMA DOS LEITORES E ESCRITORES **

/*
O problema dos Leitores e Escritores modela o acesso a uma base de dados, onde basicamente alguns processos ou threads estão lendo os dados da região crítica, 
somente querendo obter a informação da região crítica, que é o caso dos leitores, e outros processos ou threads tentando alterar a informação da região crítica, que é o caso dos escritores.

Analisando uma situação de um banco de dados localizado em um servidor, por exemplo, temos situações relacionadas ao caso do problema dos leitores e escritores. 
Supondo que temos usuários ligados a este servidor querendo ler dados em uma tabela chamada Estoque, a princípio todos os usuários terão acesso a esses dados. 
Supondo agora usuários querendo atualizar na mesma tabela de Estoque, informações de vendas realizadas, de fato esses dados serão atualizados. 
Mas para organizar esses acessos tanto de atualização, quanto leitura no banco de dados algumas políticas são seguidas, o mesmo acontecerá no problema dos leitores e escritores.

As políticas seguidas no caso dos leitores e escritores para acesso a região critica são as seguintes: processos ou threads leitores somente lêem o valor da variável compartilhada 
(não alteram o valor da variável compartilhada), podendo ser de forma concorrente; processos ou threads escritores podem modificar o valor da variável compartilhada, para isso necessita de 
exclusão mutua sobre a variável compartilhada; durante escrita do valor da variável compartilhada a operação deve ser restrita a um único escritor; para a operação de escrita não se pode 
existir nenhuma leitura ocorrendo, ou seja, nenhum leitor pode estar com a região critica bloqueada; em caso de escrita acontecendo, nenhum leitor conseguirá ter acesso ao valor da variável.

Continuando a análise do banco de dados e seguindo as políticas dos leitores e escritores têm as seguintes situações: vários usuários consultando a tabela Estoque sem alterá-la; 
para um usuário atualizar uma venda é necessário que não se tenha nenhum usuário consultando a tabela de estoque; quando um usuário estiver atualizando a venda, 
nenhum outro usuário pode atualizar ao mesmo tempo; se o usuário iniciar uma consulta e estiver ocorrendo uma atualização o mesmo irá esperar a liberação da atualização.

Por estarmos falando de um problema computacional, então como resolvermos isto computacionalmente?

*/

semaphore mutex = 1; // controla acesso a região critica

semaphore db = 1; // controla acesso a base de dados

int rc = 0; // número de processos lendo ou querendo ler”

//Tanenbaum[10]

void reader(void)

{

  while (TRUE)
  { // repete para sempre

    down(&mutex); // obtém acesso exclusivo a região critica

    rc = rc + 1; // um leitor a mais agora

    if (rc == 1)
      down(&db); //se este for o primeiro leitor bloqueia a base de dados

    up(&mutex) // libera o acesso a região critica

        read_data_base(); //acesso aos dados

    down(&mutex); // obtém acesso exclusivo a região critica

    rc = rc - 1; // menos um leitor

    if (rc == 0)
      up(&db); // se este for o último leitor libera a base de dados

    up(&mutex) // libera o acesso a região critica

        use_data_read(); // utiliza o dado
  }
}

//Tanenbaum[11].

void writer(void)

{

  while (TRUE)
  { // repete para sempre

    think_up_data(); // região não critica

    down(&db); // obtém acesso exclusivo

    write_data_base(); // atualiza os dados

    up(&db); // libera o acesso exclusivo
  }
}

//Tanenbaum[11]

// Porem se tem um problema:

// Se sempre chegarem leitores, aumentando assim o número de leitores, e existir um escritor esperando para realizar sua operação de escrita,
// o escritor pode chegar a não ser executado pelo grande número de leitores estarem sempre com a região critica bloqueada levando a uma situação caracterizada como starvation.

//Que poderia ser resolvido com um sistema de semáforos.