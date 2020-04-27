#include <cryptopp/idea.h>
#include<cryptopp/osrng.h>
#include <cryptopp/modes.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <string>

using namespace std;
using boost::lexical_cast;
using namespace CryptoPP;




 byte key[IDEA::DEFAULT_KEYLENGTH] = {
            '0', '1', '2', '3', '4', '5', '6', '7',
            '0', '1', '2', '3', '4', '5', '6', '7',
    };

byte iv[IDEA::BLOCKSIZE] = {
            0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
    };

void encrypt_idea(const std::string& filepath ){

    if (filepath.empty())
        return ;
    if(!boost::filesystem::exists(filepath))
    {
        std::cout<< "file is not exit" << std::endl;
        return;
    }
    //生成128位的随机key
    //生成随机向量


    CBC_Mode< IDEA >::Encryption e;
    e.SetKeyWithIV(key, sizeof(key), iv);
 
    const char* outfilename="encode.txt";
    FileSource(filepath.data(), true, 
        new StreamTransformationFilter(e,
            new FileSink(outfilename)));

    /*********************************\
    \*********************************/

    CBC_Mode< IDEA >::Decryption d;
    d.SetKeyWithIV(key, sizeof(key), iv);
    const char* decodefilename="decode.txt";
    FileSource(outfilename, true, 
        new StreamTransformationFilter(d,
            new FileSink(decodefilename)));

}
void string(){

encrypt_idea("student.txt");

AutoSeededRandomPool prng;

SecByteBlock key(IDEA::DEFAULT_KEYLENGTH);
prng.GenerateBlock(key, key.size());

byte iv[IDEA::BLOCKSIZE];
prng.GenerateBlock(iv, sizeof(iv));

std::string plain = "CBC Mode Test";
std::string cipher, encoded, recovered;

/*********************************\
\*********************************/

try
{
    std::cout << "plain text: " << plain << std::endl;

    CBC_Mode< IDEA >::Encryption e;
    e.SetKeyWithIV(key, key.size(), iv);

    // The StreamTransformationFilter adds padding
    //  as required. ECB and CBC Mode must be padded
    //  to the block size of the cipher.
    StringSource(plain, true, 
        new StreamTransformationFilter(e,
            new StringSink(cipher)
        ) // StreamTransformationFilter
    ); // StringSource
}
catch(const CryptoPP::Exception& e)
{
    cerr << e.what() << endl;
    exit(1);
}

/*********************************\
\*********************************/
// Pretty print
StringSource(cipher, true,
    new HexEncoder(
        new StringSink(encoded)
    ) // HexEncoder
); // StringSource

cout << "cipher text: " << encoded << endl;

/*********************************\
\*********************************/

try
{
    CBC_Mode< IDEA >::Decryption d;
    d.SetKeyWithIV(key, key.size(), iv);

    // The StreamTransformationFilter removes
    //  padding as required.
    StringSource s(cipher, true, 
        new StreamTransformationFilter(d,
            new StringSink(recovered)
        ) // StreamTransformationFilter
    ); // StringSource

    cout << "recovered text: " << recovered << endl;
}
catch(const CryptoPP::Exception& e)
{
    cerr << e.what() << endl;
    exit(1);
}
}
