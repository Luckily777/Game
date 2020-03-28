#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <assert.h>

//����ͨѶ¼��������ֵΪ200 [0-200) ǰ�պ�
#define MAX_SIZE 200
#define CAPACITY 20

//���������ϵ��Ϣ�Ľṹ�����
typedef struct PersonInof {
	char name[1024];//�洢����
	char phone[1024];//�洢�绰
}PersonInof;//����ṹ������

//����ͨѶ¼�ṹ
typedef struct AddressBook {
	PersonInof *persons;//�ܹ��ɴ洢��ͨѶ¼����
	int size;//ͳ�Ʒ���ĸ���
	//����ռ� [0- size) Ϊ��ʹ�õĿռ�
	// (size-200) Ϊδʹ�õĿռ�
	int capacity;
	//ͨѶ¼������
}AddressBook;


//�ļ��Ķ�ȡ�ʹ洢��������
void SaveFile(AddressBook* address) {
	//�ļ��洢
	//1. ���д�������Ҫд�����ݵ��ļ�
	FILE* fp = fopen("h:/address.txt", "w");
	if (fp == NULL) {
		perror("�ļ��򿪲���ʧ�ܣ�\n");
		return;
	}

	//2. ʹ��forѭ�������ķ�ʽ����ͨѶ¼֮�е�����д�뵽�ļ�֮��
	for (int i = 0; i < address->size; i++) {
		fwrite(&address->persons[i], sizeof(PersonInof), 1, fp);
	}
	fclose(fp);
	printf("����ɹ�!\n");
}





//��ʼ����������ͨѶ¼�е���Ϣ���г�ʼ��
void Init(AddressBook* address) {
	address->size = 0;//����ʹsizeΪ0 �����ʾͨѶ¼Ϊ��
	address->persons = (PersonInof*)malloc(sizeof(PersonInof) * CAPACITY);
	if (address->persons == NULL)
	{
		perror("use malloc");//����
		exit(EXIT_FAILURE);//�˳�
	}
	memset(address->persons, 0, sizeof(PersonInof) * CAPACITY);
	address->capacity = CAPACITY;
}


void CheckCapacity(AddressBook* address) {
	//����Ƿ��������꣬��������
	if (address->size == address->capacity) {
		PersonInof* ptr = (PersonInof*)realloc(address->persons,
			address->capacity * sizeof(PersonInof));
		//�������ӣ�ÿ���������������һ����׼����capacity
		if (address->persons == NULL)
		{
			//�п�
			perror("realloc");
			exit(EXIT_FAILURE);
		}
		else {
			address->persons = ptr;
		}
		printf("���ݳɹ���\n");
	}
}



//��ӡͨѶ¼�Ĳ˵�ѡ��
int Menu() {
	printf("============================\n");
	printf("==========ͨ Ѷ ¼==========\n");
	printf("======1.�� �� �� ϵ ��======\n");
	printf("======2.ɾ �� �� ϵ ��======\n");
	printf("======3.�� �� �� ϵ ��======\n");
	printf("======4.�� �� �� ϵ ��======\n");
	printf("======5.�� �� ͨ Ѷ ¼======\n");
	printf("======6.�� ӡ ͨ Ѷ ¼======\n");
	printf("======7.�� �� ͨ Ѷ ¼======\n");
	printf("======0.   ��  ��     ======\n");
	printf("============================\n");
	printf("����������ѡ��");
	int choice;
	scanf("%d", &choice);//�������ǵ�ѡ��
	return choice;///�����û����������Ϣ
}

//������ϵ�˺���
void AddpersonInof(AddressBook* address) {
	assert(address->persons != NULL);
	CheckCapacity(address);
	PersonInof* info = &address->persons[address->size];
	//��������Ϊ�˷���ʹ�ã�����������������в��ϵ�����ܳ���һ��
	printf("������������");
	scanf("%s", info->name);
	printf("������绰��");
	scanf("%s", info->phone);
	printf("�ɹ������µ���ϵ�ˣ�\n");
	address->size ++;
}

//ɾ����ϵ�˺���
void DelpersonInof(AddressBook* address) {
	//ȷ��ִ��ɾ������
	printf("ִ��ɾ��\n");
	if (address->size <= 0) {
		//�����ж�ͨѶ¼�Ƿ�Ϊ��
		printf("ͨѶ¼Ϊ�գ��������ɾ����\n");
		return;
	}

	printf("��������Ҫɾ������ϵ����ţ�");
	int id = 0;
	//������Ҫɾ������ϵ����ű���
	scanf("%d", &id);
	//�鷳֮��������Ҫ���н��в�ѯȫ������ϵ��

	if (id < 0 || id >= address->size) {
		//���ͻ�����ĳ����Ƿ�Ϸ�
		printf("�����id�Ƿ����޷�����ɾ��\n");
		return;
	}

	PersonInof* last_info = &address->persons[address->size - 1];
	//�ҵ����һ����Ա����Ϣ
	PersonInof* to_delete = &address->persons[id];
	//��Ҫɾ���ĳ�Ա��Ϣ

	*to_delete = *last_info;
	//���߽��л������
	address->size--;
	//������sizeֵ����֤ɾ����������11
	printf("ɾ���ɹ���\n");
}

void FindpersonInof(AddressBook* address) {
	printf("����ָ����ϵ��\n");
	printf("������Ҫ���ҵ���ϵ��������");
	int N = 0;
	char name[1024] = { 0 };
	//�趨�������ֵı���
	scanf("%s", name);
	for (int i = 0; i < address->size; i++) {
		//������бȶԣ�����ȵ����
		PersonInof* info = &address->persons[i];
		if (strcmp(name, info->name) == 0) {
			printf("[%d] %s:%s\n", i, info->name, info->phone);
			N++;
		}
	}
	if (N == 0) {
		printf("δ�ҵ�����Ҫ���ҵ���ϵ����Ϣ��\n");
	}
	else {
		printf("������ϵ�����\n");
	}

}

void ModifypersonInof(AddressBook* address) {
	if (address->size <= 0) {
		//ͬ���ж�ͨѶ¼�Ƿ�Ϊ��
		printf("ͨѶ¼Ϊ�գ��޷������޸�\n");
			return;
	}
	int id = 0;
	printf("������Ҫ�޸ĵ���ϵ����ţ�");
	//������ϵ������м����
	scanf("%d", &id);
	if (id < 0 || id >= address->size) {
		//�����������Ƿ�Ϸ�
		printf("��������޷���ѯ���޸�ʧ��\n");
		return;
	}

	PersonInof* info = &address->persons[id];
	//����ṹ���������
	printf("�������޸ĺ�����֣�* ��ʾ���޸ģ���");
	char name[1024] = { 0 };
	scanf("%s", name);
	//�����������޸�
	if (strcmp(name, "*") != 0) {
		strcpy(info->name, name);
	}
	printf("�������޸ĺ�ĵ绰��* ��ʾ���޸ģ���");
	char phone[1024] = { 0 };
	scanf("%s", phone);
	//ͬ��
	if (strcmp(phone, "*") != 0) {
		strcpy(info->phone, phone);
	}
	printf("�޸���ɣ�\n");
}

void PrintpersonInof(AddressBook* address) {
	printf("��ӡͨѶ¼\n");
	printf("%5s\t%10s\t%15s\t\n","num","name", "phone");
	for (int i = 0; i < address->size; i++) {
		PersonInof* info = &address->persons[i];
		printf("[%d] %s:%s\n",i,info->name,info->phone);
	}
	//�����ӡ�����ڵ�ͨѶ¼����
	printf("��ǰ����ӡ%d����¼\n", address->size);
}

void SortpersonInof(AddressBook* address) {
	int i = 0;
	int j = 0;
	int k = 0;
	for (i = 0; i < address->size - 1; i++)
	{
		for (j = 0; j < address->size - i - 1; j++)
		{
			if (strcmp(address->persons[i].name, address->persons[i + 1].name) > 0)
			{
				struct PersonInof tmp;
				tmp = address->persons[j];
				address->persons[j] = address->persons[j + 1];
				address->persons[j + 1] = tmp;
			}
		}
	}
}


void ClearpersonInof(AddressBook* address) {
	printf("�Ƿ�Ҫɾ��ȫ��ͨѶ¼��\n");
	printf("Y��y��/N��n��\n");
	//�ṩȷ��ѡ��ͻ�ѡ��
	char choice[1024] = { 0 };
	//�ش������������ɾ��
	scanf("%c", choice);
	if ((strcmp(choice, "y") == 0) || (strcmp(choice, "Y") == 0)) {
		address->size = 0;
		printf("ɾ����ϣ�\n");
		return;
	}
	//�������ȡ������
	else{
		printf("ɾ��ȡ����\n");
		return;
	}
}


void LoadFile(AddressBook* address) {
	//�ļ���ȡ
	//1. ���ļ�
	FILE* fp = fopen("h:/address.txt", "r");
	if (fp == NULL) {
		perror("�ļ��򿪲���ʧ�ܣ�\n");
		return;
	}

	//2. ѭ����ȡ�ļ�֮�е����ݣ��������ݼ��ص�ͨѶ¼�ṹ��֮��
	PersonInof tmp = { 0 };
	while (1) {
		int n = fread(&tmp, sizeof(PersonInof), 1, fp);
		if (n < 1) {
			break;
		}
		CheckCapacity(address);
		//�ж������Ƿ񳬱꣬�������ݲ���
		address->persons[address->size] = tmp;
		address->size++;
	}
	fclose(fp);

}

int main() {
	AddressBook address;//������ʼ����
	Init(&address);//��ʼ������
	LoadFile(&address);
	typedef void(*Func)(AddressBook*);
	//���庯��ָ��

	//����ת�Ʊ�ط�ʽ�����в˵���ѡ��
	Func func_table[] = {
		NULL,//Ϊ�Ͳ˵�������ƥ�䣬��0��λ����Ϊ��
		AddpersonInof,
		DelpersonInof,
		ModifypersonInof,
		FindpersonInof,
		SortpersonInof,
		PrintpersonInof,
		ClearpersonInof,
	};
	while (1) {
		int choice = Menu();
		if (choice < 0 || choice >= sizeof(func_table) / sizeof(func_table[0])) {
			printf("������������\n");
			continue;
		}
		if (choice == 0) {
			SaveFile(&address);
			system("cls");
			printf("goodbye!\n");
			break;
		}
		func_table[choice](&address);
	}

	system("pause");
	return 0;
}