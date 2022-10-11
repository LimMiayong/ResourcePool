#include<iostream>
#include<string>
#include<vector>
class GFTool{
public:
    GFTool(){};
    static std::string mul(std::string,std::string);
    static std::string add(std::string,std::string);
    static bool* string2bool(std::string);
    static std::string bool2string(bool*,int);
protected:
    static const std::string toolPolynomial; 
};
const std::string GFTool::toolPolynomial = "100011011";
std::string GFTool::mul(std::string GFA,std::string GFB){
	std::string result="0000000000000000";
	bool* gfa;
	bool* gfb;
	bool tool[8][16]={0};
	std::string toolstr[8];
	int toolNum=0;
	bool* gfc;
	bool* polynomial = string2bool(toolPolynomial);
	gfa = string2bool(GFA);
	gfb = string2bool(GFB);
	for(int i=0;i<8;i++){
		if(GFB[i]=='1'){
			for(int j=0;j<8;j++){
			   tool[toolNum][j+7-i]=gfa[j];
			}
			toolstr[toolNum] = bool2string(tool[toolNum],16);
			toolNum++;
		}
	}
	for(int i=0;i<toolNum;i++){
		result = add(result,toolstr[i]);
	}
	int pc=0;
	int x=0;
	while(true){
		for(int z=0;z<16;z++)
			tool[0][z]=0;
		gfc = string2bool(result);
		for(pc=15;pc>=0;pc--)
			if(gfc[pc]==1) break;
		if(pc<8) break;
		else{
			x = pc-8;
			for(int j=0;j<=8;j++){
			   tool[0][j+x]=polynomial[j];
			}
			toolstr[0] = bool2string(tool[0],16);
			result = add(result,toolstr[0]);	
		}
	};
	delete []gfa;
	delete []gfb;
	result = result.substr(8,15);
	return result;
}

std::string GFTool::add(std::string GFA,std::string GFB){
    int lenA = GFA.length();
    int lenB = GFB.length();
    int lenC = (lenA<lenB)?lenB:lenA;
    bool *gfa;
    bool *gfb;
    bool *gfc;
    std::string result;
    gfa = string2bool(GFA);
    gfb = string2bool(GFB);
    gfc = (lenA>lenB)?string2bool(GFA):string2bool(GFB);
    for(int i=0;i<lenC;i++){
        gfc[i]=(gfa[i]==gfb[i])?0:1;
    }
    result = bool2string(gfc,lenC);
    delete []gfa;
    delete []gfb;
    delete []gfc;
    return result;
}

bool* GFTool::string2bool(std::string str){
	int len = str.length();
	bool *result = new bool[len]; 
	for(int i=0;i<len;i++){
        result[i] = (str[len-1-i]-48);
    }
    return result;
}

std::string GFTool::bool2string(bool* bl,int len){
	std::string result;
	char bit;
	for(int i=len-1;i>=0;i--){
        bit = (bl[i]==0)?'0':'1';
        result+=bit;
    }
    return result;
}


std::string process(int AorM){
    bool TorF = true;
    if(AorM!=1&&AorM!=2) return "ProcessParameterError!!!\n";
    else{
        std::string GFA,GFB,result;
        std::cout<<"GFA  GFB";
        std::cout<<"\ninput the GFA: ";
        std::cin>>GFA;
        if(GFA.length()!=8){
            return "input Error:wrong length\n";
        }
        for(int i=0;i<GFA.length();i++)
            if(GFA[i]!='0'&&GFA[i]!='1')
                return "input Error:not 1 or 0\n";
        std::cout<<"\ninput the GFB: ";
        std::cin>>GFB;
        if(GFB.length()!=8){
            return "input Error:wrong length\n";
        }
        for(int i=0;i<GFB.length();i++)
            if(GFB[i]!='0'&&GFB[i]!='1')
                return "input Error:not 1 or 0\n";
        std::cout<<"\nthe result: \n";
        result=(AorM == 1)?GFTool::mul(GFA,GFB):GFTool::add(GFA,GFB);
        return result;
    }
}

int main(void){
    int inNum = 0;
    bool quitOrNot = false;
    while(true){
        std::cout<<"\n----Menu----\n"
                <<"1) multiplication\n"
                <<"2) additon\n"
                <<"0) exit\n"
                <<"input your choice: ";
        std::cin>>inNum;
        switch(inNum){
            case 0: 
                quitOrNot = true;
                break;
            case 1: 
                std::cout<<"mul: \n"<<process(1);
                break;
            case 2:
                std::cout<<"add: \n"<<process(2);
                break;
        }
        if(quitOrNot) break;
    }
    return 0;
}

