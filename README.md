# Projeto de Análise de Algoritmos de Ordenação

## TODO
- Implementar o algoritmo Shell Sort.
- Realizar a comparação dos resultados usando bibliotecas Python para visualização de dados.

## Descrição do Projeto

Este projeto tem como objetivo analisar o desempenho de vários algoritmos de ordenação em diferentes cenários. Os algoritmos implementados incluem:
- Insertion Sort
- Selection Sort
- Bubble Sort
- Heap Sort
- Merge Sort
- Quick Sort

O controlador principal executa os algoritmos com diferentes tamanhos e tipos de arranjos e coleta dados de desempenho, que são salvos em um arquivo CSV para posterior análise.

## Estrutura dos Arquivos

### Arquivos de Cabeçalho e Implementação
Cada algoritmo de ordenação é implementado em um arquivo de cabeçalho (`.h`) e um arquivo de implementação (`.cpp`). Os arquivos de cabeçalho contêm a declaração das funções, enquanto os arquivos de implementação contêm a lógica dos algoritmos.

### Arquivo Principal (`Main.cpp`)
O arquivo `Main.cpp` contém o controlador principal que:
- Gera diferentes tipos de arranjos.
- Executa cada algoritmo de ordenação.
- Coleta e salva os dados de desempenho em um arquivo CSV.

### Configuração do VS Code
Dois arquivos importantes para a configuração do VS Code são:
- `tasks.json`: Define a tarefa de compilação.
- `launch.json`: Configura a depuração do código.

#### `tasks.json`
Este arquivo define como compilar o projeto utilizando o compilador `g++`.

```json
{
  "version": "2.0.0",
  "tasks": [
    {
      "label": "build",
      "type": "shell",
      "command": "g++",
      "args": [
        "-g",
        "Main.cpp",
        "InsertionSort.cpp",
        "SelectionSort.cpp",
        "BubbleSort.cpp",
        "HeapSort.cpp",
        "MergeSort.cpp",
        "QuickSort.cpp",
        "ShellSort.cpp"
        "-o",
        "sorting_analysis"
      ],
      "group": {
        "kind": "build",
        "isDefault": true
      },
      "problemMatcher": ["$gcc"],
      "detail": "Compilação do projeto de ordenação"
    }
  ]
}
```

#### `launch.json`
Este arquivo configura a depuração do código no VS Code.

```json
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "(gdb) Launch",
      "type": "cppdbg",
      "request": "launch",
      "program": "${workspaceFolder}/sorting_analysis",
      "args": [],
      "stopAtEntry": false,
      "cwd": "${workspaceFolder}",
      "environment": [],
      "externalConsole": false,
      "MIMode": "gdb",
      "setupCommands": [
        {
          "description": "Enable pretty-printing for gdb",
          "text": "-enable-pretty-printing",
          "ignoreFailures": true
        }
      ],
      "preLaunchTask": "build",
      "miDebuggerPath": "C:\\mingw-w64\\bin\\gdb.exe",
      "internalConsoleOptions": "openOnSessionStart"
    }
  ]
}
```

## Como Executar o Código

### Configuração no VS Code

1. **Instalar MinGW**:
   - Baixe e instale o MinGW [MinGW-w64](http://mingw-w64.org/doku.php/download/mingw-builds).
   - Adicione o caminho do diretório `bin` do MinGW ao PATH do sistema.

2. **Instalar Extensões do VS Code**:
   - Instale a extensão `C/C++` da Microsoft.
   - (Opcional) Instale a extensão `Code Runner`.

3. **Configurar `tasks.json` e `launch.json`**:
   - Adicione os arquivos `tasks.json` e `launch.json` ao diretório `.vscode` do seu projeto.

4. **Compilar o Projeto**:
   - Pressione `Ctrl+Shift+B` para compilar o projeto.

5. **Executar o Projeto**:
   - Pressione `Ctrl+Alt+N` (se estiver usando o Code Runner) ou execute o executável gerado diretamente do terminal.

### Compilação via Linha de Comando

1. **Abra o terminal do Git Bash**.

2. **Navegue até o diretório do projeto**:
   ```sh
   cd /caminho/para/o/projeto
   ```

3. **Compile o código**:
   ```sh
   g++ -g Main.cpp InsertionSort.cpp SelectionSort.cpp BubbleSort.cpp HeapSort.cpp MergeSort.cpp QuickSort.cpp ShellSort.cpp -o sorting_analysis
   ```

4. **Execute o executável gerado**:
   ```sh
   ./sorting_analysis
   ```

## Coleta de Dados

O programa gera um arquivo `sorting_results.csv` contendo os dados de desempenho de cada algoritmo de ordenação. Este arquivo pode ser utilizado para análise e visualização dos dados utilizando bibliotecas Python como `pandas` e `matplotlib`.

### Leitura dos Dados no Python

TODO