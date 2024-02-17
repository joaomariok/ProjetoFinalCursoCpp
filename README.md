# ProjetoFinalCursoCpp
Repositório para o projeto final do curso de C++

## Grupo G9:
- João Mário Künzle Ribeiro Magalhães
- Julia Minetto Macias
- Matheus Barbosa
- Thiago Freitas

## Documentos
* Documento de UML (ProjetoFinalCursoCpp\Documents\UML.pdf)
* Documento de Requisitos (ProjetoFinalCursoCpp\Documents\?)

## Como buildar o projeto (Visual Studio 2022)
* Clone o repositório
* Abra a solution (ProjetoFinalCursoCpp\TrucoGame\TrucoGame.sln)
* Configure para Debug x64 e clique em "Local Windows Debugger"
* Após executar o jogo e inserir o nome dos jogadores, 2 dialogs novos vão aparecer: Jogador 1 e Jogador 2 (ficando 3 ao todos). Lembre-se de mover eles para conseguir visualizá-los. 

 ## Recomendações
 * Recomendamos executar o projeto em monitores com Escala 100%. Caso contrário alguns problemas de UI podem acontecer.

## Dicas para build do projeto (Visual Studio 2022)
* Certifique-se que as seguintes cargas de trabalho estão instaladas:

Desenvolvimento para desktop com .NET / Desenvolvimento para desktop com C++
![workloads](https://github.com/joaomariok/ProjetoFinalCursoCpp/assets/65927068/eaa41de0-5d81-4611-b4d1-8961887b86f6)

* E os seguintes componentes individuais:

C++ MFC for latest v143 build tools (x86 & x64) / C++ MFC for v141 build tools (x86 & x64)
![image](https://github.com/joaomariok/ProjetoFinalCursoCpp/assets/65927068/6065e6db-d6bf-4b01-84ae-752a60bad366)

C++ ATL for latest v143 build tools (x86 & x64) / C++ ATL for v141 build tools (x86 & x64)
![image](https://github.com/joaomariok/ProjetoFinalCursoCpp/assets/65927068/1f51f214-df15-4550-9600-d006f91bbea3)

* Altere a propriedade (Use of MFC) do projeto para: **Use MFC in a Shared DLL**

![image](https://github.com/joaomariok/ProjetoFinalCursoCpp/assets/65927068/8b2c440f-959f-494c-bb38-576b9eae49df)

### Referências / links úteis
https://stackoverflow.com/questions/25031009/error-please-define-afxdll-or-do-not-use-mdd-occurs-even-after-making-chang

https://stackoverflow.com/questions/29898486/cannot-open-source-file-afxwin-h-afxext-h-afxdisp-h-afxdtctl-h-afxcmn-h
