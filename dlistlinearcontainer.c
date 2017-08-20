

typedef struct _PrivInfo
{
    dlist* dlst;
}PrivInfo;


static Ret linear_container_dlist_insert(LinearContainer* thiz, size_t index, void* data)
{
    PrivInfo* priv = (PrivInfo*)thiz->priv;

    return dlist_insert(priv->dlist, index, data);
}

static Ret linear_container_dlist_delete(LinearContainer* thiz, size_t index)
{
    PrivInfo* priv = (PrivInfo*)thiz->priv; 

    return dlist_delete(priv->dlist, index);
} 

LinearContainer* linear_container_dlist_create(DataDestroyFunc data_destroy, void* ctx)
{
    LinearContainer* thiz = (LinearContainer*)malloc(sizeof(LinearContainer) + sizeof(PrivInfo)); 

    if(thiz != NULL)
    {
        PrivInfo* priv = (PrivInfo*)thiz->priv;
        priv->dlist = dlist_create(data_destroy, ctx); 

        thiz->insert        =  linear_container_dlist_insert;
        thiz->prepend       =  linear_container_dlist_prepend;
        thiz->append        =  linear_container_dlist_append;
        thiz->del           =  linear_container_dlist_delete;
        thiz->get_by_index  =  linear_container_dlist_get_by_index;
        thiz->set_by_index  =  linear_container_dlist_set_by_index;
        thiz->length        =  linear_container_dlist_length;
        thiz->find          =  linear_container_dlist_find;
        thiz->foreach       =  linear_container_dlist_foreach;
        thiz->destroy       =  linear_container_dlist_destroy; 

        if(priv->dlist == NULL)
        {
            free(thiz);
            thiz = NULL;
        }
    }
}
