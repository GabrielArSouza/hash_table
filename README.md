# hash_table
###Implementação de uma tabela hash
## Sobre o projeto

<p>
	Este projeto foi escrito em linguagem C++, utiliza um arquivo make para compilação e o arquivo src/driver_hash.cpp contém testes para os métodos implementados, os arquivos das classes HashTbl e HashEntry podem ser encontrados na pasta include.
</p>
<p>
	O HashTbl é a construção de uma classe para o uso de uma tabela hash, sua implementação 
	busca o aperfeiçoamento das habilidades na implementação de classes e tabelas hash. Este projeto é semelhante ao container associativo std::unordered_map encontrado na biblioteca <unordered_map> do STL.
</p>
<p>
	Juntamente com a tabela hash foi implementado seu uso por meio de uma pequena aplicação de contas de um banco, o struct Account, encontrado no driver_hash.cpp, representa o tipo de dado de uma conta, outros structs foram criados para representar a função de dispersão pensada para esse tipo de implementação e também para realizar a comparação de duas chaves ( iguais ou diferentes ). A tabela hash sempre tem o tamanho de um número primo, se o usuário especificar um tamanho não primo, a classe busca o próximo número primo para então criar a tabela.
</p>

## Como executar

| #       | Descrição           | Comando  |
| :------------- |:-------------| :-----|
| 1      | Compilar | ```$ make``` |
| 2      | Executar   | ```$ ./build/bin ``` |


## Autoria

Desenvolvido por Gabriel Araújo de Souza (<gabriel_feg@hotmail.com >)

2017.1

&copy; IMD/UFRN 2017.