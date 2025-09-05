import numpy as np
import sys

#np.set_printoptions(formatter={'float': lambda x: "{0:0.7f}".format(x)})
#np.set_printoptions(linewidth=np.inf)

class tableau:
    def __init__(self,):
        self.tabela = []
        self.var = 0
        self.res = 0
        self.bases = []
        self.obj = []

    def inicializa_tabela(self):
        rest, var = input().split()
        self.res = int(rest)
        self.var = int(var)
        self.obj = np.zeros(self.var, dtype=float)
        self.tabela = np.zeros((self.res + 1, self.var + 1), dtype=float)

        c = input().split()
        for i in range(len(c)):
            self.tabela[0][i] = int(c[i]) * -1
            self.obj[i] = int(c[i]) * -1
        
        for i in range(1, len(self.tabela)):
            arr = input().split()
            self.tabela[i] = np.array(arr)
        
        #Faz a matriz vero
        aux = np.eye(self.res, dtype=float)
        toprow = np.zeros(self.res)
        aux = np.insert(aux, 0, toprow, axis=0)

        self.tabela = np.concatenate((aux,self.tabela),axis=1)
    
    def checa_b(self):
        for i in range(1, len(self.tabela)):
            if self.tabela[i][-1] < 0:
                self.tabela[i] = self.tabela[i] * -1

    def checa_fim(self):
        if min(self.tabela[0][self.res:-1]) >= 0:
            return True
        else:
            return False
    
    def pivoteia(self,index_col):
        #pega index da linha a ser pivoteada
        index_lin = 0
        val_lin = sys.float_info.max
        for i in range(1, len(self.tabela)):
            if self.tabela[i][index_col] > 0:
                val = self.tabela[i][-1] / self.tabela[i][index_col]
                if val < val_lin:
                    val_lin = val
                    index_lin = i 
        #print("index lin : ", index_lin)
        #troca a base
        for i in range(self.bases.size):
            if self.bases[i] == 1:
                if self.tabela[index_lin][i] == 1:
                    self.bases[i] = 0
                    break
        self.bases[index_col] = 1

        #divide a linha pelo valor encontrado para que ela tenha 1

        self.tabela[index_lin] = self.tabela[index_lin] / self.tabela[index_lin][index_col]

        #zera a coluna
        for i in range(len(self.tabela)):
            if i != index_lin:
                self.tabela[i] = self.tabela[i] - self.tabela[i][index_col] * self.tabela[index_lin]
        #print(self.tabela)
        
    def simplex(self):
        ilimitada = False
        for i in range(len(self.obj)):
            self.tabela[0][i+self.res] = self.obj[i]
        #pega o b
        b = self.tabela[:, -1]
        self.tabela = self.tabela[:, 0:-1]
        

        #adiciona as var de folga
        aux = np.eye(self.res, dtype=float)
        toprow = np.zeros(self.res)
        aux = np.insert(aux, 0, toprow, axis=0)
        self.tabela = np.concatenate((self.tabela,aux),axis=1)
        self.tabela = np.hstack((self.tabela, np.atleast_2d(b).T))

        #print(self.tabela)
        #define as bases
        self.bases = np.zeros(self.tabela[0].size)
        for i in range(self.res+self.var, self.tabela[0].size - 1):
            self.bases[i] = 1
        #print(self.tabela)
        fim = self.checa_fim()

        while not fim:
            #pega index da coluna a ser pivoteada
            index_col = 0
            for i in range(self.res, len(self.tabela[0])):
                if self.tabela[0][i] < 0:
                    index_col = i
                    break
            #print("index col : ", index_col)

            for i in range( len(self.tabela)):
                if self.tabela[i][index_col] > 0:
                    ilimitada = False
                    break
                else:
                    ilimitada = True
            
            if ilimitada:
                print("ilimitada")
                #print(self.tabela)

                for i in range(self.res,len(self.bases) - self.res - 1):
                    self.bases[i] = 1

                sol = np.zeros(len(self.bases))
                sol[index_col]=0
                for i in range(self.res,len(self.bases - self.res -1)):
                    if self.bases[i] == 1:
                        for j in range(1,len(self.tabela)):
                            if self.tabela[j][i] == 1:
                                sol[i] = self.tabela[j][-1]
                for i in range(self.res,len(self.bases) - self.res -1):
                    print('{0:.7f}'.format(sol[i]),end=" ")
                print()
                for i in range(0,self.res):
                    print('{0:.7f}'.format(self.tabela[0][i]),end=" ")
                #print(self.tabela[0][0:self.res])
                break

                
            self.pivoteia(index_col)
            fim = self.checa_fim()

        if ilimitada:
            return
        elif(self.tabela[0][-1] < 0):
            print("inviavel")
            for i in range(0,self.res):
                print('{0:.7f}'.format(self.tabela[0][i]),end=" ")
        elif(self.tabela[0][-1] >= 0):

            print("otima")
            #dropa vars inuteis
            self.tabela =  np.delete(self.tabela,np.s_[self.res+self.var:self.tabela[0].size-1],1)
            self.bases = np.delete(self.bases,np.s_[self.res+self.var:-1])
            print("%0.7f" % self.tabela[0][-1])
            sol = np.zeros(len(self.bases))
            for i in range(len(self.bases)):
                if self.bases[i] == 1:
                    for j in range(1,len(self.tabela)):
                        if self.tabela[j][i] == 1:
                            sol[i] = self.tabela[j][-1]
            for i in range(self.res,len(self.bases) - 1):
                print('{0:.7f}'.format(sol[i]),end=" ")
            print()
            for i in range(0,self.res):
                print('{0:.7f}'.format(self.tabela[0][i]),end=" ")

        



if __name__ == '__main__':

    matrix = tableau()
    matrix.inicializa_tabela()
    matrix.simplex()
    #matrix.imprime_tabela()
    #matrix.checa_fim()

