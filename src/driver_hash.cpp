/**
 * @file drive_hash.cpp
 * @author Gabriel Araújo de Souza
 * @date 13 Jun 2017
 * @brief Arquivo contendo os testes e uso da tabela hash
 *        implementada na classe HashTbl
 */

#include <iostream> //<! std::cout 
#include <string>	//<! std::string
#include <utility>	//<! std::hash<std::string>, std::hash<int>
#include <tuple>	//<! tuple
#include <cassert>  //<! assert

#include "hashtable.h"

//<! Definindo tupla
using AcctKey = std::tuple< std::string, int , int , int >;

/**
 * @brief      Tipo de dado ( conta do banco )
 */
struct Account 
{
	std::string name; //<! Nome
	int bank;		  //<! Código do banco
	int branch;		  //<! Agência da conta
	int account;	  //<! Número da conta
	float balance;	  //<! Saldo da conta
	AcctKey key;	  //<! Chave da conta

	/**
	 * @brief      Constutor
	 *
	 * @param[in]  n     Nome do usuário da conta
	 * @param[in]  b     Codigo do banco
	 * @param[in]  bn    Agência da conta
	 * @param[in]  ac    Número da conta
	 * @param[in]  blc   Dinheiro da conta
	 */
	Account( std::string n = "gabriel", int b=1, int bn=1,
			 int ac=1, float blc=1.00 )
			: name ( n )
			, bank ( b )
			, branch ( bn )
			, account ( ac )
			, balance ( bn )
			, key (n, b, bn, ac)
	{ /*empty*/ }

	/**
	 * @brief      Pega a chave da conta
	 *
	 * @return     A chave da conta.
	 */
	AcctKey get_key() const
	{
		return key;
	} 
};

/**
 * @brief      Função de hash primária
 */
struct KeyHash 
{
	/**
	 * Cria uma chave com base nos dados da conta
	 */
	std::size_t operator()( const AcctKey & k_ ) const
	{
		auto name = std::get<0>(k_);
		auto bank = std::get<1>(k_);
		auto bran = std::get<2>(k_);
		auto acco = std::get<3>(k_);

		std::hash<std::string> hash_str;
		std::hash< int > hash_int;

		return ( (hash_str(name)) xor (hash_int(bank)) xor
				 (hash_int(bran)) xor (hash_int(acco)));
	}
};

/**
 * @brief      Compara se duas chaves são iguais
 */
struct KeyEqual
{
	/**
	 * Compara se duas tuplas são iguais.
	 */
	bool
	operator()( const AcctKey & rhs_, 
				const AcctKey & lhs_ ) const
	{
		return rhs_ == lhs_;
	}
};

int main ()
{
	HashTbl<AcctKey, Account, KeyHash, KeyEqual> tb;
	
	//<! Criando dados. 
	Account a = {"Alex Bastos", 1, 1668, 54321, 1500.00 };
	Account b = {"Aline Souza", 1, 1668, 45794, 530.00};
	Account c = {"Cristiano Ronaldo", 13, 557, 87629, 150000.00};
	Account d = {"Jose Lima", 18, 331, 1231, 850.00};
	Account e = {"Saulo Cunha", 116, 666, 84312, 5490.00};

	//<! testando o insert
	tb.insert(a.get_key(), a);
	tb.insert(b.get_key(), b);
	tb.insert(c.get_key(), c);
	tb.insert(d.get_key(), d);
	tb.insert(e.get_key(), e);

	assert( tb.count() == 5 );
	
	tb.print();

	//<! Testando Remove
	tb.remove(d.get_key());
	std::cout << "\n";
	assert( tb.count() == 4 );

	tb.print();
	
	tb.remove(d.get_key());
	assert( tb.count() == 4 );


	//<! Testando Retrieve
	Account var;
	assert( tb.retrieve(e.get_key(), var));
	std::cout << "\n>>>Resultado da busca: " << var.name << "\n";
	assert((tb.retrieve(d.get_key(), var)) == false );

	//<! Testando clear
	tb.clear();
	std::cout << "\n";
	tb.print();
	assert( tb.count() == 0 );

	//<! Testando o empty
	assert( tb.empty() );
	tb.insert(a.get_key(), a);
	assert( (tb.empty()) == false );
	assert( tb.count() == 1 );

	//<! testando is_prime
	assert( is_prime(11));
	assert( is_prime(47));
	assert( is_prime(997));
	assert( is_prime(4517));

	//<! testando next_prime
	assert( next_prime(110) == 113 );
	assert( next_prime(24) == 29);
	assert( next_prime(3824) == 3833);

	HashTbl<AcctKey, Account, KeyHash, KeyEqual> test(21);
	assert(test.capacity() == 23);

	HashTbl<AcctKey, Account, KeyHash, KeyEqual> tt(5);
	//<! testando rehash
	tt.insert(a.get_key(), a);
	tt.insert(b.get_key(), b);
	tt.insert(c.get_key(), c);
	tt.insert(d.get_key(), d);
	tt.insert(e.get_key(), e);

	tt.print();

	std::cout << "\n >>>Passou em todos os testes. \n";
	return 0;

}