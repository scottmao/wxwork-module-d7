<?php
function wxwork_get_apps() {
    $output = "<div><a href='/admin/config/wxwork/app/add'>增加应用</a></div>";
    $output .= "<table><thead><th>ID</th><th>app_id</th><th>secret</th><th>agent_id</th><th>操作</th></thead>";

    $results = $query = db_select('wxwork_app_config', 'ac')
        ->fields('ac')
        ->execute()
        ->fetchAll();

    if (empty($results)) {
        $output = "<tr colspan='2'><td>还没有应用相关的配置，请点击<a href='/admin/config/wxwork/config/add'>增加应用</a>. </td></tr>";
        return $output;
    }
    else {
        for ($i = 0; $i < count($results); $i++) {
            $result = $results[$i];
            if($i % 2 === 0){
                $output .= "<tr class='odd'>";
            }
            else {
                $output .= "<tr class='even'>";
            }
            $output .= "<td>" . $result->id . "</td>";
            $output .= "<td>" . $result->app_id . "</td>";
            $output .= "<td>" . $result->secret . "</td>";
            $output .= "<td>" . $result->agent_id . "</td>";
            $output .= "<td>" . l(t('菜单管理'), 'admin/config/wxwork/menu/' . $result->id) . "&nbsp;&nbsp;"
                . l(t('消息管理'), 'admin/config/wxwork/msg/' . $result->id) . "</td></tr>";
        }
    }
    $output .= "</table>";

    return $output;
}