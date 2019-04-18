#ifndef FIO_OPT_GROUP_H
#define FIO_OPT_GROUP_H

struct opt_group {
	const char *name;
	uint64_t mask;
};

enum opt_category {
	__FIO_OPT_C_GENERAL	= 0,
	__FIO_OPT_C_IO,
	__FIO_OPT_C_FILE,
	__FIO_OPT_C_STAT,
	__FIO_OPT_C_LOG,
	__FIO_OPT_C_PROFILE,
	__FIO_OPT_C_ENGINE,
	__FIO_OPT_C_NR,

	FIO_OPT_C_GENERAL	= (1ULL << __FIO_OPT_C_GENERAL),
	FIO_OPT_C_IO		= (1ULL << __FIO_OPT_C_IO),
	FIO_OPT_C_FILE		= (1ULL << __FIO_OPT_C_FILE),
	FIO_OPT_C_STAT		= (1ULL << __FIO_OPT_C_STAT),
	FIO_OPT_C_LOG		= (1ULL << __FIO_OPT_C_LOG),
	FIO_OPT_C_PROFILE	= (1ULL << __FIO_OPT_C_PROFILE),
	FIO_OPT_C_ENGINE	= (1ULL << __FIO_OPT_C_ENGINE),
	FIO_OPT_C_INVALID	= (1ULL << __FIO_OPT_C_NR),
};

enum opt_category_group {
	__FIO_OPT_G_RATE	= 0,
	__FIO_OPT_G_ZONE,
	__FIO_OPT_G_RWMIX,
	__FIO_OPT_G_VERIFY,
	__FIO_OPT_G_TRIM,
	__FIO_OPT_G_IOLOG,
	__FIO_OPT_G_IO_DEPTH,
	__FIO_OPT_G_IO_FLOW,
	__FIO_OPT_G_DESC,
	__FIO_OPT_G_FILENAME,
	__FIO_OPT_G_IO_BASIC,
	__FIO_OPT_G_CGROUP,
	__FIO_OPT_G_RUNTIME,
	__FIO_OPT_G_PROCESS,
	__FIO_OPT_G_CRED,
	__FIO_OPT_G_CLOCK,
	__FIO_OPT_G_IO_TYPE,
	__FIO_OPT_G_THINKTIME,
	__FIO_OPT_G_RANDOM,
	__FIO_OPT_G_IO_BUF,
	__FIO_OPT_G_TIOBENCH,
	__FIO_OPT_G_ERR,
	__FIO_OPT_G_E4DEFRAG,
	__FIO_OPT_G_NETIO,
	__FIO_OPT_G_RDMA,
	__FIO_OPT_G_LIBAIO,
	__FIO_OPT_G_ACT,
	__FIO_OPT_G_LATPROF,
	__FIO_OPT_G_RBD,
	__FIO_OPT_G_HTTP,
	__FIO_OPT_G_GFAPI,
	__FIO_OPT_G_MTD,
	__FIO_OPT_G_HDFS,
	__FIO_OPT_G_SG,
	__FIO_OPT_G_MMAP,
	__FIO_OPT_G_NR,

	FIO_OPT_G_RATE		= (1ULL << __FIO_OPT_G_RATE),
	FIO_OPT_G_ZONE		= (1ULL << __FIO_OPT_G_ZONE),
	FIO_OPT_G_RWMIX		= (1ULL << __FIO_OPT_G_RWMIX),
	FIO_OPT_G_VERIFY	= (1ULL << __FIO_OPT_G_VERIFY),
	FIO_OPT_G_TRIM		= (1ULL << __FIO_OPT_G_TRIM),
	FIO_OPT_G_IOLOG		= (1ULL << __FIO_OPT_G_IOLOG),
	FIO_OPT_G_IO_DEPTH	= (1ULL << __FIO_OPT_G_IO_DEPTH),
	FIO_OPT_G_IO_FLOW	= (1ULL << __FIO_OPT_G_IO_FLOW),
	FIO_OPT_G_DESC		= (1ULL << __FIO_OPT_G_DESC),
	FIO_OPT_G_FILENAME	= (1ULL << __FIO_OPT_G_FILENAME),
	FIO_OPT_G_IO_BASIC	= (1ULL << __FIO_OPT_G_IO_BASIC),
	FIO_OPT_G_CGROUP	= (1ULL << __FIO_OPT_G_CGROUP),
	FIO_OPT_G_RUNTIME	= (1ULL << __FIO_OPT_G_RUNTIME),
	FIO_OPT_G_PROCESS	= (1ULL << __FIO_OPT_G_PROCESS),
	FIO_OPT_G_CRED		= (1ULL << __FIO_OPT_G_CRED),
	FIO_OPT_G_CLOCK		= (1ULL << __FIO_OPT_G_CLOCK),
	FIO_OPT_G_IO_TYPE	= (1ULL << __FIO_OPT_G_IO_TYPE),
	FIO_OPT_G_THINKTIME	= (1ULL << __FIO_OPT_G_THINKTIME),
	FIO_OPT_G_RANDOM	= (1ULL << __FIO_OPT_G_RANDOM),
	FIO_OPT_G_IO_BUF	= (1ULL << __FIO_OPT_G_IO_BUF),
	FIO_OPT_G_TIOBENCH	= (1ULL << __FIO_OPT_G_TIOBENCH),
	FIO_OPT_G_ERR		= (1ULL << __FIO_OPT_G_ERR),
	FIO_OPT_G_E4DEFRAG	= (1ULL << __FIO_OPT_G_E4DEFRAG),
	FIO_OPT_G_NETIO		= (1ULL << __FIO_OPT_G_NETIO),
	FIO_OPT_G_RDMA		= (1ULL << __FIO_OPT_G_RDMA),
	FIO_OPT_G_LIBAIO	= (1ULL << __FIO_OPT_G_LIBAIO),
	FIO_OPT_G_ACT		= (1ULL << __FIO_OPT_G_ACT),
	FIO_OPT_G_LATPROF	= (1ULL << __FIO_OPT_G_LATPROF),
	FIO_OPT_G_RBD		= (1ULL << __FIO_OPT_G_RBD),
	FIO_OPT_G_HTTP		= (1ULL << __FIO_OPT_G_HTTP),
	FIO_OPT_G_GFAPI		= (1ULL << __FIO_OPT_G_GFAPI),
	FIO_OPT_G_MTD		= (1ULL << __FIO_OPT_G_MTD),
	FIO_OPT_G_HDFS		= (1ULL << __FIO_OPT_G_HDFS),
	FIO_OPT_G_SG		= (1ULL << __FIO_OPT_G_SG),
	FIO_OPT_G_MMAP		= (1ULL << __FIO_OPT_G_MMAP),
	FIO_OPT_G_INVALID	= (1ULL << __FIO_OPT_G_NR),
};

extern const struct opt_group *opt_group_from_mask(uint64_t *mask);
extern const struct opt_group *opt_group_cat_from_mask(uint64_t *mask);

#endif
