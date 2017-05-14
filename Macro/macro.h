typedef struct mnt{
	char name[24];
	int no_pp;
	int no_kp;
	int no_ev;
	struct mdt *mdtp;
	struct fpt *fptp;
	struct kpt *kptp;			
}mnt;

struct mdt{
	char a[100][100];
	int no;
};

typedef struct param{
	char name[24];
	char value[24];
}param;

typedef struct fpt{
	param a[24];
}fpt;

typedef struct kpt{
	param a[24];
}kpt;
