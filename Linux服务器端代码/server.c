#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<json/json.h>
#include<string.h>


int get_json_int_filed(const char *json_data,const char *filed)//整数型值的读取
{
	int filed_value;
	json_object *jobject;
	
	jobject = json_tokener_parse(json_data);
	if(jobject == NULL)
	{
		printf("json data error\n");
		return -1;
	}

	struct json_object *filed_object = json_object_object_get(jobject,filed);//

	if(filed_object == NULL)
	{
		printf("json object is not exist %s filed\n",filed);
		return -1;
	}
	

	filed_value = json_object_get_int(filed_object);
	json_object_put(filed_object);//释放filed_object
	json_object_put(jobject);
	return filed_value;
}

char *get_json_string_filed(const char *json_data,const char *filed)//字符串类型数据读取
{
	char *str;
	const char *filed_value;
	json_object *jobject;
	jobject = json_tokener_parse(json_data);
	if(jobject == NULL)
	{
		printf("json data error\n");
		return NULL;
	}
	
	struct json_object *filed_object = json_object_object_get(jobject,filed);//读取对象中成员的json对象

	if(filed_object == NULL)
	{
		printf("json object is not string exist %s  filed\n",filed);
		return NULL;
	}

	filed_value = json_object_get_string(filed_object);

	str = strdup(filed_value);//将filed_value保存在str中，防止被释放后乱码
	json_object_put(filed_object);
	json_object_put(jobject);
	
	return str;
}

void control_device1(int control_statu)
{
	if(control_statu == 0)
	{
		printf("open device1\n");
	}
	else{
		printf("close device1\n");
	}
}

void control_device2(int control_statu)
{
	if(control_statu == 0)
	{
		printf("open device2\n");
	}
	else{
		printf("close device2\n");
	}
}

void control_device3(int control_statu)
{
	if(control_statu == 0)
	{
		printf("open device3\n");
	}
	else{
		printf("close device3\n");
	}
}

void control_device4(int control_statu)
{
	if(control_statu == 0)
	{
		printf("open device4\n");
	}
	else{
		printf("close device4\n");
	}
}

void control_device(int deviceId,int control_statu)
{
	switch(deviceId)
	{
	case 1:
		control_device1(control_statu);
		break;

	case 2:
		control_device2(control_statu);
		break;

	case 3:
		control_device3(control_statu);
		break;

	case 4:
		control_device4(control_statu);
	}

	return;
}

void client_control(int sockfd,const char *json_data)
{
	int deviceId;
	int control_statu;
	char *clientId = get_json_string_filed(json_data,"clientId");
	
	if(clientId == NULL)
	{
		return;
	}

	
	if(getppid() != atoi(clientId))//对比父进程id
	{
		free(clientId);
		return;
	}

	control_statu = get_json_int_filed(json_data,"controlStatu");
	deviceId = get_json_int_filed(json_data,"deviceId");

	control_device(deviceId,control_statu);

	free(clientId);

	return;
}


void ack_client_rebuild(int sockfd,int exist_flag)//修改结果返回
{
	const char *json_data;
	char *error_string;
	//char *forget_password;

	json_object *jobject;
	printf("flag = %d\n",exist_flag);
	jobject = json_object_new_object();
	json_object_object_add(jobject,"functionId",json_object_new_int(5));//添加json对象的成员
	json_object_object_add(jobject,"statu",json_object_new_int(exist_flag));//添加json对象的成员exist_flag的值作为statu判断，1为错误，0为正确

	if(exist_flag)
	{
		//forget_password = password; 
		error_string = "信息填写错误";
		printf("error flag : %d\n",exist_flag);
	
	}
	else{
printf("true flag : %d\n",exist_flag);
		error_string = "";

	}
	
	json_object_object_add(jobject,"error",json_object_new_string(error_string));//添加json对象的成员，error_string作为error的错误原因
	
	
	json_data = json_object_to_json_string(jobject);
	printf("result : %s\n",json_data);

	write(sockfd,json_data,strlen(json_data));
	json_object_put(jobject);

	return;
}

void client_build(int sockfd,const char *json_data)//修改密码
{
	//printf("client_build\n");
	int exist_flag = 0;
	char *oldpassword = get_json_string_filed(json_data,"oldpassword");
	char *newpassword = get_json_string_filed(json_data,"newpassword");
	char *email = get_json_string_filed(json_data,"email");
	char *name = get_json_string_filed(json_data,"name");
	char *username;
	char *phone;
	char *r_email;
	char buff[1024] = {'\0'};
	FILE *fp;
	FILE *fp1;
	fp = fopen("user1.txt","a+");
	fp1 = fopen("_user1.txt","a+");
	
	int i = 0;

	while(1)
	{
		char _username[100];
		char _password[100];
		char _phone[100];
		char _email[100];

		if(fgets(buff,sizeof(buff),fp) == NULL){
			break;
		}

		int ret = sscanf(buff,"%[^:]:%[^:]:%[^:]:%s\n",_username,_password,_phone,_email);
		
		//printf("email : %s\n",email);
		//printf("phone : %s\n",_phone);
		//printf("_email: %s\n",_email);
printf("----------\n");
		int a = strcmp(email,_phone);
		printf("a = %d\n",a);

		if(a == 0)
		{
printf("----------\n");
			//printf("oldpassword : %s\n",oldpassword);
			//printf("_password : %s\n",_password);
		int b = strcmp(oldpassword,_password);
printf("b = %d\n",b);
			if(b != 0)
			{
			
			exist_flag = 1;//旧密码错误
			printf("go to next\n");
			goto next;
			}


			username = _username;
			r_email = _email;
			phone = _phone;		
			
			i = 1;
		}
		//printf("user = %s\n",_username);
		
		else
		{
			printf("2\n");
			fputs(buff,fp1);
		}
		printf("1\n");
	
	}
        if(i == 0)
	{	
		exist_flag = 1;//没有找到用户
		goto next;
		printf("i = 0 goto exit\n");		
	}
//printf("newpassword : %s\n",newpassword);

	fprintf(fp1,"%s:%s:%s:%s\n",username,newpassword,phone,r_email);
printf("username : %s\n",username);
printf("newpassword : %s\n",newpassword);
printf("phone : %s\n",phone);
printf("r_email : %s\n",r_email);
	fclose(fp);
	fclose(fp1);
   	remove("user1.txt");
	rename("_user1.txt","user1.txt");
	
next:
	remove("_user1.txt");
	free(oldpassword);
	free(newpassword);
	free(email);
	free(name);
	//free(username);
	//free(phone);
	//free(r_email);
	printf("rebuild_flag : %d\n",exist_flag);
	ack_client_rebuild(sockfd,exist_flag);

	return;

}


void ack_client_login(int sockfd,int exist_flag)//判断登录成功或失败
{
	const char *json_data;
	char *error_string;
	json_object *jobject;
	printf("login...\n");
	jobject = json_object_new_object();
	json_object_object_add(jobject,"functionId",json_object_new_int(2));//添加json对象的成员
	json_object_object_add(jobject,"statu",json_object_new_int(exist_flag));//添加json对象的成员exist_flag的值作为statu判断，1为错误，0为正确

	if(exist_flag)
	{
		
		error_string = "登录名或密码错误";
		
	}
	else{
		char clientId[100];
		error_string = "";
		sprintf(clientId,"%d",getppid());
		json_object_object_add(jobject,"clientId",json_object_new_string(clientId));
	}

	json_object_object_add(jobject,"error",json_object_new_string(error_string));//添加json对象的成员，error_string作为error的错误原因

	json_data = json_object_to_json_string(jobject);

	write(sockfd,json_data,strlen(json_data));
	json_object_put(jobject);

	return;
}

void client_login(int sockfd,const char *json_data)
{
	FILE *fp;
	
	int exist_flag = 1;
	char *username = get_json_string_filed(json_data,"username");
	char *password = get_json_string_filed(json_data,"password");
	char register_username[100];
	char register_password[100];
	char register_telephone[100];
	char register_email[100];

	fp = fopen("user1.txt","a+");

	if(fp == NULL)
	{
		perror("fail to user1.txt");
		return;
	}
	while(1)
	{
		int ret = fscanf(fp,"%[^:]:%[^:]:%[^:]:%s\n",register_username,register_password,register_telephone,register_email);
	printf("login ter = %d \n",ret);
		if(ret == EOF)
		{
			break;
		}

		if(strcmp(username,register_username) == 0 && strcmp(password,register_password) == 0)
		{
			exist_flag = 0;
			goto next;
printf("login goto next.....\n");
		}
	}


next:
	
	fclose(fp);
	free(username);
	free(password);
	ack_client_login(sockfd,exist_flag);

	return;

}

void ack_client_register(int sockfd,int exist_flag)//判断注册成功或失败
{
	const char *json_data;
	char *error_string;
	json_object *jobject;
printf("register...\n");
	jobject = json_object_new_object();
	json_object_object_add(jobject,"functionId",json_object_new_int(1));//添加json对象的成员
	json_object_object_add(jobject,"statu",json_object_new_int(exist_flag));//添加json对象的成员exist_flag的值作为statu判断，1为错误，0为正确

	if(exist_flag)
	{
		error_string = "error";
	}
	else{
		error_string = "";
	}

	json_object_object_add(jobject,"error",json_object_new_string(error_string));//添加json对象的成员，error_string作为error的错误原因

	json_data = json_object_to_json_string(jobject);

	write(sockfd,json_data,strlen(json_data));
	json_object_put(jobject);

	return;
}

void client_register(int sockfd,const char *json_data)//注册用户名的写入以及读取
{
	FILE *fp;
	int exist_flag = 0;
	char *username = get_json_string_filed(json_data,"username");
	char *password = get_json_string_filed(json_data,"password");
	char *telephone = get_json_string_filed(json_data,"phone");
	char *email = get_json_string_filed(json_data,"email");

	fp = fopen("user1.txt","a+");//创建并打开user.txt
	if(fp == NULL)
	{
		perror("fail to open");
		return;
	}
	while(1)
	{
		char _username[100];
		char _password[100];
		char _telephone[100];
		char _email[100];
		int ret = fscanf(fp,"%[^:]:%[^:]:%[^:]:%s\n",_username,_password,_telephone,_email);//从文件中读取四个数据
		printf("register ter = %d \n",ret);
		if(ret == EOF)
		{
			break;
		}
		
		if(strcmp(username,_username)==0 && strcmp(email,_email) && strcmp(telephone,_telephone))
		{
			exist_flag = 1;
			goto next;//直接去next：
printf("register goto next.....\n");
		}
	}
	fprintf(fp,"%s:%s:%s:%s\n",username,password,telephone,email);//将四个数据写进文件

next:
	fclose(fp);//关闭txt
	free(username);
	free(password);
	free(telephone);
	free(email);
	ack_client_register(sockfd,exist_flag);

	return;
}


void ack_client_forget(int sockfd,int exist_flag,char *password)//返回用户信息
{
	const char *json_data;
	char *error_string;
	//char *forget_password;

	json_object *jobject;
printf("forget...\n");
	jobject = json_object_new_object();
	json_object_object_add(jobject,"functionId",json_object_new_int(4));//添加json对象的成员
	json_object_object_add(jobject,"statu",json_object_new_int(exist_flag));//添加json对象的成员exist_flag的值作为statu判断，1为错误，0为正确

	if(exist_flag)
	{
		//forget_password = password; 
		error_string = password;
		printf("error_string : %s\n",error_string);
	}
	else{
		error_string = "";
	}
	
	json_object_object_add(jobject,"error",json_object_new_string(error_string));//添加json对象的成员，error_string作为error的错误原因

	json_data = json_object_to_json_string(jobject);

	write(sockfd,json_data,strlen(json_data));
	json_object_put(jobject);

	return;
}

void client_forget(int sockfd,const char *json_data)//忘记密码的读取
{
	FILE *fp;
	int exist_flag = 0;
	char *password;
	char *username = get_json_string_filed(json_data,"username");
	char *telephone = get_json_string_filed(json_data,"phonenumber");
	char *email = get_json_string_filed(json_data,"email");

	fp = fopen("user1.txt","a+");//创建并打开user.txt
	if(fp == NULL)
	{
		perror("fail to open");
		return;
	}
	while(1)
	{
		char _username[100];
		char _password[100];
		char _telephone[100];
		char _email[100];
		int ret = fscanf(fp,"%[^:]:%[^:]:%[^:]:%s\n",_username,_password,_telephone,_email);//从文件中读取四个数据
	printf("forget ter = %d \n",ret);
		if(ret == EOF)
		{
			break;
		}
		
		if(strcmp(username,_username) == 0 )
		{
			password = _password;
			exist_flag = 1;
			goto next;
printf("forget goto next.....\n");
		}
	}
	

	next:
	fclose(fp);//关闭txt
	free(username);
//	free(telephone);
//	free(email);
	ack_client_forget(sockfd,exist_flag,password);

	return;
}




void process_task(int sockfd,const char *json_data)//判断functionId的数值
{
	int functionId;

	functionId = get_json_int_filed(json_data,"functionId");
	if(functionId < 0)
	{
		return;
	}

	switch(functionId)
	{
		case 1://注册
			client_register(sockfd,json_data);
			break;

		case 2://登录
			client_login(sockfd,json_data);
			break;

		case 3:
			client_control(sockfd,json_data);
			break;

		case 4:
			client_forget(sockfd,json_data);
			break;
		
		case 5:
			client_build(sockfd,json_data);
			break;
	}
}



void do_client(int sockfd)
{
	int ret;
	char buf[1024];

	while(1)
		{
			ret = read(sockfd,buf,sizeof(buf)-1);
			if(ret <= 0)
			{
				break;
			}
			buf[ret] = '\0';
			printf("read : %d,bytes : %s\n",ret,buf);
			
			process_task(sockfd,buf);
		}
	exit(0);
}

int main(int argc, const char *argv[])
{
	int listenfd,ret,clientfd;
	char buf[1024];
	pid_t pid;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	int addrlen = sizeof(clientfd); 
	listenfd=socket(AF_INET,SOCK_STREAM,0);
	if(listenfd<0)
	{
		perror("Fail to create scket");
		return -1;
	}
	printf("socket id: %d\n",listenfd);
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(8080);
	server_addr.sin_addr.s_addr=inet_addr("192.168.1.112");
	ret=bind(listenfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
	if(ret<0)
	{
		perror("Fail to bind");
		return -1;
	}

	ret=listen(listenfd,128);
	if(ret<0)
	{
		perror("Fail to listen");
		return -1;
	}
	printf("listen ...\n");
	while(1)
	{
		clientfd = accept(listenfd,(struct sockaddr *)&client_addr,&addrlen);
		if(clientfd<0)
		{
			perror("Fail to accept");
			return -1;
		}

		pid = fork();
		if(pid < 0)
		{
			perror("Fail to work");
			return -1;
		}

		if(pid == 0)
		{
			close(listenfd);
			do_client(clientfd);
		}
		close(clientfd);
	}
	return 0;
}
