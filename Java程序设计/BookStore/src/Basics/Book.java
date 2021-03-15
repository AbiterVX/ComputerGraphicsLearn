package Basics;

import java.sql.*;
import java.util.Vector;

/***
 * #Book���ʵ����
 */

public class Book {
/*--------------------------------------����---------------------------------------*/
	private String id;  			//��ı�ʶ
	private String name;     		// #�������
	private double price;   		//#��ļ�Ǯ
	private String type;   			//#������
	private String picture_path; 	//#���ͼƬ�����·��
	private int sales_volume;		//����
/*--------------------------------------����---------------------------------------*/
	public Book(ResultSet resultset){		
		try {
			id=resultset.getString(1);
			name=resultset.getString(2);
			price=resultset.getDouble(3);
			type=resultset.getString(4);
			picture_path=resultset.getString(5);
			sales_volume=resultset.getInt(6);
		} catch (SQLException e) {
			System.out.println("Book��ResultSet�������");
			//e.printStackTrace();
		}		
	}
	public Book(String TheBookId,String TheBookName,double ThePrice,String TheType,String ThePicture,int TheVolume){
		id=TheBookId;
		name=TheBookName;
		price=ThePrice;
		type=TheType;
		picture_path=ThePicture;
		sales_volume=TheVolume;
	}	
	
/*--------------------------------------�õ���Ϣ-----------------------------------*/	
	public String GetId(){
		return id;
	}
	public String GetName(){
		return name;
	}
	public double GetPrice(){
		return price;
	}
	public String GetType(){
		return type;
	}
	public String GetPicturePath(){
		return picture_path;
	}
	public int GetSalesVolume(){
		return sales_volume;
	}
/*--------------------------------------����book��Ϣ-------------------------------*/	
	public void SetId(String TheId){
		id=TheId;
	}	
	public void SetName(String TheName){
		name=TheName;
	}	
	public void SetPrice(double ThePrice){	
		price=ThePrice;
	}	
	public void SetType(String TheType){
		type=TheType;
	}
	public void SetPicturePath(String ThePicture){
		picture_path=ThePicture;
	}		
	public void SetSalesVolume(int TheSalesVolume){
		sales_volume=TheSalesVolume;
	}	
}

























