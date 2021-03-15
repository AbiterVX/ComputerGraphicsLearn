package Basics;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Vector;


/***
 * user�ฺ�������ͨ�û��Ĳ���������
 */

public class User 
{
/*--------------------------------------����---------------------------------------*/
	private String user_id;           	//�û���Ψһ��ʶ
	private String user_name;    		//�û����û���
	private String pass_word;    		//�û�������
	private int user_type;				//�û�����
	private double wallet;       		//Ǯ��
	
	//private Vector shopping_cart;		//��¼�����û��Ĺ��ﳵ��Ϣ����¼��ı��
	//private Vector history;      		//��¼�Ѿ������ı��
/*--------------------------------------����---------------------------------------*/
	public User(ResultSet resultset) {
		try {
			user_id=resultset.getString(1);
			user_name=resultset.getString(2);
			pass_word=resultset.getString(3);
			user_type=resultset.getInt(4);
			wallet=resultset.getDouble(5);
		} catch (SQLException e) {
			System.out.println("User��ResultSet�������");
			//e.printStackTrace();
		}	
	}
	public User(String TheUserId,String TheUserName,String ThePassWord,int TheUserType,double TheWallet){
		user_id=TheUserId; 
		user_name=TheUserName; 	
		pass_word=ThePassWord;
		user_type=TheUserType;
		wallet=TheWallet; 	
	}
	
/*--------------------------------------�õ���Ϣ-----------------------------------*/
	public String GetId(){
		return user_id;
	}
	public String GetUserName(){
		return user_name;
	}
	public String GetPassWord(){
		return pass_word;
	}
	public int GetUserType(){
		return user_type;
	}	
	public double GetWallet(){
		return wallet;
	}
	
/*--------------------------------------�����û���Ϣ-------------------------------*/	
	public void SetUserId(String TheUserName){
		user_id=TheUserName;
	}
	public void SetUserName(String TheUserName){
		user_name=TheUserName;
	}
	public void SetPassWord(String ThePassWord){
		pass_word=ThePassWord;
	}	
	public void SetUserType(short TheUserType){
		user_type=TheUserType;
	}	
	public void SetWallet(double TheWallet){
		wallet=TheWallet;
	}		

}

















































