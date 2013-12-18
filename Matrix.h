/*
	版本号:
		0.2.1版本。
	
	新增：
		增加了数乘，相加。
		增加了使用数组构造。
		增加了转置。
		增加了无参数构造。
		增加了reSize()动态更改矩阵尺寸的函数。更改后的矩阵全部被置0.
		增加了isEmpty()函数。

	bug修复：
		修复了矩阵相乘bug.
		修复了数乘矩阵只能乘整型的bug.
		修复了矩阵转置的结果只能是整型矩阵的bug.

	作者：
		绵里针
*/
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
using namespace std;
template <class T>
class CMatrix
{
public:
       T* pMat;
	   CMatrix()
       {
            this->n=0;
            this->m=0;
            pMat=NULL;
       }
       CMatrix(int m,int n)
       {
            this->n=n;
            this->m=m;
            pMat=new T[n*m];
            memset(pMat,0,n*m*sizeof(T));
       }
       CMatrix(CMatrix<T>& matrix)
       {
            this->n=matrix.n;
            this->m=matrix.m;
            pMat=new T[matrix.n*matrix.m];
            memcpy(pMat,matrix.pMat,n*m*sizeof(T));
       }
	   CMatrix(T* pData,int rows,int cols)
       {
            this->m=rows;
            this->n=cols;
            pMat=new T[rows*cols];
			memcpy(pMat,pData,rows*cols*sizeof(T));
       }
	   bool reSize(int rows,int cols)
	   {
		   this->m=rows;
		   this->n=cols;
		   CMatrix<T> newMatrix(rows,cols);
		   delete[] pMat;
		   pMat=newMatrix.setNull();
		   return true;
	   }
	   bool isEmpty()
	   {
		   return this->m==0||this->n==0;
	   }
       T& valueOf(int r,int c)
       {
             return pMat[r*n+c];    
       }
       int show()
       {
           for(int i=0;i<m;i++)
           {
                for(int j=0;j<n;j++)
                {
                     cout<<valueOf(i,j)<<' ';
                }
                cout<<endl;
           }
           return 0;
       }
       CMatrix<T> operator*(CMatrix<T>& matrix)
       {
           if(getColNum()!=matrix.getRowNum()) return CMatrix<T>(1,1);
           CMatrix<T> r(getRowNum(),matrix.getColNum());
           for(int i=0;i<r.getRowNum();i++)
           {
                for(int j=0;j<r.getColNum();j++)
                {
                     r.valueOf(i,j)=0;
                     for(int k=0;k<getColNum();k++)
                     {
                          r.valueOf(i,j)=(T)(r.valueOf(i,j)+valueOf(i,k)*matrix.valueOf(k,j));
                     }
                }
           }
           return r;
       }
	   T* setNull()//设置矩阵数据位NULL,但不释放内存空间，返回空间的指针。
	   {
		   T* tmp=pMat;
		   pMat=NULL;
		   m=0;
		   n=0;
		   return tmp;
	   }
	   CMatrix<T> operator+(CMatrix<T>& m)
       {
           if(getRowNum()!=m.getRowNum()||getColNum()!=m.getColNum()) return CMatrix<T>(1,1);
           CMatrix<T> r(*this);
           for(int i=0;i<getRowNum();i++)
           {
                for(int j=0;j<m.getColNum();j++)
                {
					r.valueOf(j,i)+=m.valueOf(j,i);
                }
           }
           return r;
       }
	   CMatrix<T> operator+=(CMatrix<T>& m)
       {
           if(getRowNum()!=m.getRowNum()||getColNum()!=m.getColNum()) return CMatrix<T>(1,1);
           for(int i=0;i<getRowNum();i++)
           {
                for(int j=0;j<m.getColNum();j++)
                {
					valueOf(j,i)+=m.valueOf(j,i);
                }
           }
           return *this;
       }
	   CMatrix<double>& transposition()
	   {
		   CMatrix<T> r(getColNum(),getRowNum());
		   for(int i=0;i<getRowNum();i++)
		   {
			   for(int j=0;j<getColNum();j++)
			   {
				   r.valueOf(j,i)=valueOf(i,j);
			   }
		   }
		   delete[] pMat;
		   swap(m,n);
		   pMat=r.setNull();
		   return *this;
	   }
       int getRowNum()
       {
           return m;
       }
       int getColNum()
       {
           return n;
       }
       ~CMatrix()
       {
            if(pMat!=NULL) delete[] pMat;     
       }
	   template <class NUMTYPE>
	   friend CMatrix<T> operator*(NUMTYPE num,CMatrix<T> m)
	   {
		   int i=0,j=0;
		   CMatrix<T> r(m);
		   for(i=0;i<m.getRowNum();i++)
		   {
			   for(j=0;j<m.getColNum();j++)
			   {
					r.valueOf(i,j)*=num;
			   }
			}
		   return r;
	   }
	   template <class NUMTYPE>
	   friend CMatrix<T> operator*(CMatrix<T> m,NUMTYPE num)
	   {
		   int i=0,j=0;
		   CMatrix<T> r(m);
		   for(i=0;i<m.getRowNum();i++)
		   {
			   for(j=0;j<m.getColNum();j++)
			   {
					r.valueOf(i,j)*=num;
			   }
			}
			return r;
	   }
private:
       int m;//行数
       int n;//列数
};

#endif
