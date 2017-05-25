<?php

function wxwork_app_form($form, &$form_state) {
    $form['wxwork_appid'] = array(
        '#type' => 'textfield',
        '#title' => t('AppID'),
        '#required' => TRUE,
    );
    $form['wxwork_secret'] = array(
        '#type' => 'textfield',
        '#title' => t('AppSecret'),
        '#required' => TRUE,
    );
    $form['wxwork_entrance'] = array(
        '#type' => 'textfield',
        '#title' => t('入口URL'),
        '#required' => TRUE,
    );
    $form['wxwork_agentid'] = array(
        '#type' => 'textfield',
        '#title' => t('agent_id'),
        '#required' => TRUE,
    );

    // 可以加验证方法
    //$form['#validate'] = array('myform_page_form_validate');

    $form['submit'] = array(
        '#type' => 'submit', // 提交按钮
        '#value' => '确认提交', // 按钮值
        '#submit' => array('wxwork_app_form_submit'), // 提交函数
    );

    return $form;
}

function wxwork_app_form_submit(&$form, &$form_state) {
    $wid = db_insert('wxwork_app_config')
        ->fields(array(
            'app_id' => $form_state['values']['wxwork_appid'],
            'secret' => $form_state['values']['wxwork_secret'],
            'entrance' => $form_state['values']['wxwork_entrance'],
            'agent_id' => $form_state['values']['wxwork_agentid'],
            'create_time' => time()
        ))
        ->execute();

    // 获取上一条 insert sql 返回的主键，以此判断是否执行成功
    if ($wid) {
        drupal_set_message('新应用已经提交');

        // 如果想将用户重定向到一个页面，可修改 $form['#redirect'] 值，如：
        drupal_goto('/admin/config/wxwork/config');
    }
    else {
        // 数据写入失败了
        drupal_set_message('抱歉，新应用增加失败', 'error');
    }
}